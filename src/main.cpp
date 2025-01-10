#include <iostream>
#include <string>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  std::string player_name, level;
  int level_number;
  std::cout<< "Please enter your unique name: ";
  std::getline(std::cin, player_name);
  
 
  do{
		std::cout << "Please choose the game level (1 --> 3): \n 1- Easy\n 2- Meduim\n 3- Hard\n";
  		std::getline(std::cin, level);
  		// Convert the string to an integer
  		level_number = std::stoi(level);
    	if(level_number < 1 || level_number > 3)
          	std::cout << "Incorrect number\n";
  }while(level_number < 1 || level_number > 3);
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
   
  Game game(kGridWidth, kGridHeight, player_name, static_cast<Difficulty>(level_number));
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  
  if(!game.GetSnakeStaus())
  {
  	  // show a dialog box
      std::string msgText{"Player Name: "+ player_name +"\nScore: " + std::to_string(game.GetScore()) + "\nSize: " + std::to_string(game.GetSize()) + "\nPlayer High Score: " + std::to_string(game.GetHighScore(player_name))};
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "You died!", msgText.c_str(), NULL);  
  }
  return 0;
}