#include <iostream>
#include "game.h"
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, std::string player_name, Difficulty level)
    : snake(grid_width, grid_height),
	  player_data("high_scores.txt"),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
	  player_name(player_name),
	  obstacle(grid_width, grid_height),
     difficulty(level){
    
  if (difficulty == Difficulty::Medium || difficulty == Difficulty::Hard) {
    obstacle.AddWallObstacle();
  }
  if (difficulty == Difficulty::Hard) {
    obstacle.AddRandomObstacle();
  }
    PlaceFood(food);  
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  StartBonusFoodThread(); // Start the bonus food thread

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, pause_game);
     if (!pause_game) {
      	Update();
    	renderer.Render(snake, food, bonus_food, show_bonus_food, obstacle.GetObstacles());
    }else
    {
      	// Render a pause overlay or screen
      	renderer.RenderPauseOverlay();
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000 && !pause_game) {
      int high_score = player_data.loadData(player_name);
      if(high_score == -1) //player doesn`t exist
      {
        	high_score = score;
      }
      else
      {
        	high_score = (high_score < score? score : high_score);
      }
      
      player_data.saveData(player_name, high_score);

      
      renderer.UpdateWindowTitle(player_name, score, frame_count, high_score);
      if (difficulty == Difficulty::Hard && snake.alive) {
        	if(not_add_rand_obst)
            {
              	std::thread obstacleTimer(TimerThread, &not_add_rand_obst);
      			    obstacleTimer.detach();
            }
        	else
            {
        		    obstacle.RemoveRandomObstacle();
    			      obstacle.AddRandomObstacle();
              	not_add_rand_obst = true;
            }
 	 }
      
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
      StopBonusFoodThread(); // Stop the bonus food thread

}

void Game::PlaceFood(SDL_Point &food) {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !obstacle.ObstacleCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood(food);
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
    
    std::uniform_int_distribution<int> random_poison_food(1, 10);

     // 20 percentage change for the poisonous food
    if(random_poison_food(engine) <= 2){
      snake.poison_snake = true;
      // resolves 5 seconds later
      std::thread poisonTimer(TimerThread, &snake.poison_snake);
      poisonTimer.detach();
    }
  }
  
  // Check for bonus food
    {
        std::lock_guard<std::mutex> lock(bonus_mutex);
        if (show_bonus_food && !bonus_food_consumed && 
            bonus_food.x == new_x && bonus_food.y == new_y) {
            score += 3; // Increase score by 3
            bonus_food_consumed = true; // Mark bonus food as consumed
          	show_bonus_food = false;
        }
    }
  
  // Check collisions with all obstacles (walls + random)
  	if(obstacle.ObstacleCell(new_x, new_y)){
      snake.alive = false;
      return;
    }
}

// Poison timer, if the snake get poisoned the thread 
// will return snake to normal after 5 seconds
void Game::TimerThread(bool *param) {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    // get back to normal after 5 seconds
    *param = false;
}

void Game::StartBonusFoodThread() {
    stop_bonus_thread = false;
    bonus_food_thread = std::thread(&Game::BonusFoodThread, this);
}

void Game::StopBonusFoodThread() {
    {
        std::lock_guard<std::mutex> lock(bonus_mutex);
        stop_bonus_thread = true;
    }
    bonus_cv.notify_one(); // Wake up the thread to exit
    if (bonus_food_thread.joinable()) {
        bonus_food_thread.join();
    }
}

void Game::BonusFoodThread() {
    while (true) {
        {
            std::unique_lock<std::mutex> lock(bonus_mutex);
            if (stop_bonus_thread) {
                break; // Exit the thread if stopping
            }
        }

      	// Wait for 30 seconds before showing the bonus food
        //std::this_thread::sleep_for(std::chrono::seconds(30));

        // Place bonus food and make it visible
      	if(snake.alive)
        {
            std::lock_guard<std::mutex> lock(bonus_mutex);
            PlaceFood(bonus_food);
            show_bonus_food = true;
            bonus_food_consumed = false; // Reset the flag
        }

        // Bonus food is displayed for 5 seconds
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // Hide bonus food
        {
            std::lock_guard<std::mutex> lock(bonus_mutex);
            show_bonus_food = false;
        }

        // Wait 5 seconds before showing the bonus food again
        std::this_thread::sleep_for(std::chrono::seconds(25));
    }
}



int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
bool Game::GetSnakeStaus() const{ return snake.alive; }
int Game::GetHighScore(std::string &player) const {return player_data.loadData(player); }