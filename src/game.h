#ifndef GAME_H
#define GAME_H

#include <random>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "player_high_score.h"
#include "obstacle.h"

enum class Difficulty { noLevel, Easy, Medium, Hard };

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, std::string player_name, Difficulty level);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  bool GetSnakeStaus() const;
  int GetHighScore(std::string &player) const;

 private:
  Snake snake;
  SDL_Point food;
  PlayerHighScore player_data;
  Difficulty difficulty;
  Obstacle obstacle;  // For random obstacles
  SDL_Point bonus_food;
  
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::thread bonus_food_thread; // Thread for bonus food
  std::mutex bonus_mutex; // Mutex to synchronize access to shared data
  std::condition_variable bonus_cv; // Condition variable for thread communication

  int score{0};
  std::string player_name;
  bool pause_game{false};
  bool not_add_rand_obst{true};
  bool bonus_food_consumed{false}; // check if the bonus food is eaten
  bool show_bonus_food{false}; // Whether bonus food is currently displayed
  bool stop_bonus_thread{false}; // Flag to stop the thread

  
  void PlaceFood(SDL_Point &food);
  void Update();
  static void TimerThread(bool *poisoned);
  void StartBonusFoodThread(); // Start the bonus food thread
  void StopBonusFoodThread();  // Stop the bonus food thread
  void BonusFoodThread();      // Thread function for managing bonus food
};

#endif