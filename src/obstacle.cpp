#include "obstacle.h"
#include <random>
#include <iostream>
Obstacle::Obstacle(int grid_width, int grid_height)
    : grid_width(grid_width), grid_height(grid_height) {}

void Obstacle::AddRandomObstacle() {
  std::random_device dev;
  std::mt19937 engine(dev());
  std::uniform_int_distribution<int> random_w(0, grid_width - 1);
  std::uniform_int_distribution<int> random_h(0, grid_height - 1);

  SDL_Point new_obstacle;
  new_obstacle.x = random_w(engine);
  new_obstacle.y = random_h(engine);

  obstacles.emplace_back(new_obstacle);
}

void Obstacle::AddWallObstacle()
{
	for (int i = 0; i < grid_width; ++i) {
    // Top and bottom walls
    obstacles.emplace_back(SDL_Point{i, 0});                     // Top wall
    obstacles.emplace_back(SDL_Point{i, static_cast<int>(grid_height - 1)}); // Bottom wall
  }
  for (int i = 0; i < grid_height; ++i) {
    // Left and right walls
    obstacles.emplace_back(SDL_Point{0, i});                     // Left wall
    obstacles.emplace_back(SDL_Point{static_cast<int>(grid_width - 1), i}); // Right wall
  }  
}

void Obstacle::RemoveRandomObstacle()
{
	if(!obstacles.empty())
    {
     	SDL_Point last_obs =  obstacles.back();
      
      	/*Remove obstacle only in case it is not a part of the wall*/
      	if(last_obs.x > 0 && last_obs.x < grid_width -1 && last_obs.y > 0 && last_obs.y < grid_height - 1)
        {
          	obstacles.pop_back();
        }
    }
}

bool Obstacle::ObstacleCell(int x, int y) const {
  for (auto const &cell : obstacles) {
    if (x == cell.x && y == cell.y) {
      return true;
    }
  }
  return false;
}
std::vector<SDL_Point> Obstacle::GetObstacles() const { return obstacles; }
