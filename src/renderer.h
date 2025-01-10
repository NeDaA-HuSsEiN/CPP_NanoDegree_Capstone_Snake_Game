#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include "SDL.h"
#include "snake.h"
#include "obstacle.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, SDL_Point const &bonus_food, bool show_bonus_food, std::vector<SDL_Point> const &obstacles);
  void UpdateWindowTitle(std::string player_name, int score, int fps, int high_score);
  void RenderPauseOverlay();
    
 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif