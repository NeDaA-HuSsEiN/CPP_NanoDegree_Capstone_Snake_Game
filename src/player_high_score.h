#ifndef PLAYER_HIGH_SCORE_H
#define PLAYER_HIGH_SCORE_H

#include <string>
#include <vector>

class PlayerHighScore {
private:
    // Struct to represent a player
    struct Player {
        std::string name;
        int highScore;
    };
    std::string filename; // The filename where the data is saved

public:
    // Constructor that initializes the filename
    PlayerHighScore(const std::string& filename);

    // Function to load the high score of a specific player
    int loadData(const std::string& player_name) const;

    // Function to save or update player data
    void saveData(const std::string& player_name, int high_score);

};

#endif // PLAYER_HIGH_SCORE_H
