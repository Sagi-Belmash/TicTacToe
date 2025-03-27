//
// Created by sagib on 21/01/2025.
//

#ifndef TICTACTOE_GAME_H
#define TICTACTOE_GAME_H
#include <vector>
#include <iostream>

class Game {
private:
    // Constructs the game instance
    Game();
    // Deconstructs the game instance
    ~Game();
    // Delete copy constructor and assignment operator
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    // The X places vector
    std::vector<int> xVec;
    // The O places vector
    std::vector<int> oVec;
    // The current player
    char currPlayer = 'X';

public:
    // Returns the instance of the gameljwfvwvwnkl;
    static Game& getInstance();
    // Clears the symbol vectors
    void resetGame();
    // If possible, places the current symbol on the dessired row and column
    bool makeMove(int row, int col);
    // Return true if the current player has won
    bool checkWin(int* begin, int* end);
    // Switches the current player
    void switchPlayer();
    // Returns the symbol of the current player
    char getCurrentPlayer();
};


#endif //TICTACTOE_GAME_H
