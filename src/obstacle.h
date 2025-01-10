#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include "SDL.h"

class Obstacle {
 public:
  Obstacle(int grid_width, int grid_height);
  void AddRandomObstacle();
  void AddWallObstacle();
  std::vector<SDL_Point> GetObstacles() const;
  bool ObstacleCell(int x, int y) const;
  void RemoveRandomObstacle();
 private:
  int grid_width;
  int grid_height;
  std::vector<SDL_Point> obstacles;
};

#endif
