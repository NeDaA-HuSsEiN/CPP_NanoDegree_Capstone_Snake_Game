# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## New Features Added

1. The user enters his name and choose the level of the game.
2. There are three levels in the game:
   * Easy level: The same Udacity project without any obstacles.
   * Medium level: Adding a wall around the screen.
   * Hard level: Adding the wall as well as random obstacles.
3. Save the name and the player's high score in a text file.
4. Add poisoned food that makes the snake go in the reverse direction in case it ate it.
5. Add bonus food that increases the score by 3.
6. The user can press P to pause to resume the game.
7. Display dialogue when the player lose to tell him the high score and the current score.

## Rubric Points

1. The project reads data from a file and process the data, or the program writes data to a file. --> high_scores.txt
2. The project accepts user input and processes the input. --> Get the name of the player and the level of the game.
3. The project demonstrates an understanding of C++ functions and control structures. --> Added different functions in controller, game, and renderer module.
4. The project uses data structures and immutable variables. --> Define obstacles vector in obstacle.h
5. One or more classes are added to the project with appropriate access specifiers for class members. --> Added two new classes which are obstacle, and player_high_score classes.
6. Class constructors utilize member initialization lists. --> In obstacle, and player_high_score classes.
7. Classes abstract implementation details from their interfaces. --> In obstacle, and player_high_score classes.
8. The project makes use of references in function declarations. --> function HandleInput takes pass the 3rd param by reference. Also, function Render pass some param by reference.
9. The project uses multithreading. --> In game class.
10. A mutex or lock is used in the project. --> In game class.
11. A condition variable is used in the project. --> In game class.
12. The project follows the Rule of 5. --> In renderer class
13. The project uses destructors appropriately. --> In player_high_Score class

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
