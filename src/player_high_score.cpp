#include <iostream>
#include <fstream>
#include <sstream>
#include "player_high_score.h"

// Constructor that initializes the filename
PlayerHighScore::PlayerHighScore(const std::string& file) : filename("../" + file), players(nullptr), playerCount(0) {
 	// Attempt to open the file for writing. If it doesn't exist, create it.
    std::ofstream fileStream(filename, std::ios::app);
    if (!fileStream) {
        std::cerr << "Failed to create or open the file: " << filename << std::endl;
    }
    // Closing file after ensuring it exists.
    fileStream.close();
}

PlayerHighScore::~PlayerHighScore() {
    // Free dynamically allocated memory
    delete[] players;
}

// Function to load the high score of a specific player
int PlayerHighScore::loadData(const std::string& name) const {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string playerName;
            int score;
            if (std::getline(iss, playerName, ':') && (iss >> score)) {
                if (playerName == name) {
                    file.close();
                    return score;
                }
            }
        }
        file.close();
    }
    return -1; // If player not found, return -1
}

// Function to save or update player data
void PlayerHighScore::saveData(const std::string& name, int score) {
  std::ifstream file(filename);
    std::vector<Player> tempPlayers;
    bool playerFound = false;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string playerName;
            int playerScore;
            if (std::getline(iss, playerName, ':') && (iss >> playerScore)) {
                if (playerName == name) {
                    tempPlayers.push_back({playerName, score});
                    playerFound = true;
                } else {
                    tempPlayers.push_back({playerName, playerScore});
                }
            }
        }
        file.close();
    }

    if (!playerFound) {
        tempPlayers.push_back({name, score});
    }

    // Allocate memory for players dynamically
    playerCount = tempPlayers.size();
    players = new Player[playerCount];
    for (std::size_t i = 0; i < playerCount; ++i) {
        players[i] = tempPlayers[i];
    }

    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (std::size_t i = 0; i < playerCount; ++i) {
            outFile << players[i].name << ": " << players[i].highScore << std::endl;
        }
        outFile.close();
    }
}
