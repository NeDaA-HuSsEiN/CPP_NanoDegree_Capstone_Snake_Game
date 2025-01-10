#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height){
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(sdl_renderer);
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

Renderer::Renderer(Renderer&& other) noexcept
    : sdl_window(other.sdl_window), sdl_renderer(other.sdl_renderer),
      screen_width(other.screen_width), screen_height(other.screen_height),
      grid_width(other.grid_width), grid_height(other.grid_height) {
  other.sdl_window = nullptr;
  other.sdl_renderer = nullptr;
}

Renderer& Renderer::operator=(Renderer&& other) noexcept {
  if (this != &other) {
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);

    // Move ownership of SDL resources
    sdl_window = other.sdl_window;
    sdl_renderer = other.sdl_renderer;

    // Keep the const members as they are
    // No need to reassign screen_width, screen_height, grid_width, grid_height

    other.sdl_window = nullptr;
    other.sdl_renderer = nullptr;
  }
  return *this;
}

void Renderer::Render(Snake const snake, SDL_Point const &food, SDL_Point const &bonus_food, bool show_bonus_food, std::vector<SDL_Point> const &obstacles) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  //Render obstacles
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x88, 0xFF);
  for (auto const &obstacle : obstacles) {
    block.x = obstacle.x * block.w;
    block.y = obstacle.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }
  
  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render bonus food if active
  if (show_bonus_food) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF); // Green color
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;
    block.x = bonus_food.x * block.w;
    block.y = bonus_food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
   }
  
  // Render snake's body
  // if snake get poisoned render a green body
  if(snake.poison_snake){
    SDL_SetRenderDrawColor(sdl_renderer, 0xBE, 0xD3, 0x3D, 0xFF); // green color
  }else{
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  }
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);
 
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(std::string player_name, int score, int fps, int high_score) {
  std::string title{"Player name: "+ player_name+ " Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) + " Player High Score: " + std::to_string(high_score)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}


void Renderer::RenderPauseOverlay() {

  std::string title{"Paused, click P again to resume playing"};
  SDL_SetWindowTitle(sdl_window, title.c_str());
  SDL_RenderPresent(sdl_renderer);  
}
