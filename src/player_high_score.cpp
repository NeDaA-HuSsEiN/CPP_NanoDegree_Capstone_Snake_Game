#include <iostream>
#include <fstream>
#include <sstream>
#include "player_high_score.h"

// Constructor that initializes the filename
PlayerHighScore::PlayerHighScore(const std::string& file) : filename("../" + file) {
 	// Attempt to open the file for writing. If it doesn't exist, create it.
    std::ofstream fileStream(filename, std::ios::app);
    if (!fileStream) {
        std::cerr << "Failed to create or open the file: " << filename << std::endl;
    }
    // Closing file after ensuring it exists.
    fileStream.close();
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

    // Read the existing players and their scores
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string playerName;
            int playerScore;
            if (std::getline(iss, playerName, ':') && (iss >> playerScore)) {
                if (playerName == name) {
                    // Update score if player is found
                    tempPlayers.push_back({playerName, score});
                    playerFound = true;
                } else {
                    tempPlayers.push_back({playerName, playerScore});
                }
            }
        }
        file.close();
    }

    // If the player was not found, add a new record
    if (!playerFound) {
        tempPlayers.push_back({name, score});
    }

    // Rewrite the file with the updated data
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& player : tempPlayers) {
            outFile << player.name << ": " << player.highScore << std::endl;
        }
        outFile.close();
    }
}
