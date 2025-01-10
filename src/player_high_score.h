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
    Player* players; // Pointer to dynamically allocated array
    std::size_t playerCount; // Number of players in the array
public:
    // Constructor that initializes the filename
    PlayerHighScore(const std::string& filename);

    // Destructor that free dynamically allocated memory
  	~PlayerHighScore();
    // Function to load the high score of a specific player
    int loadData(const std::string& player_name) const;

    // Function to save or update player data
    void saveData(const std::string& player_name, int high_score);

};

#endif // PLAYER_HIGH_SCORE_H
