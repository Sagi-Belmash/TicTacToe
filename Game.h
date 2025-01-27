//
// Created by sagib on 21/01/2025.
//

#ifndef TICTACTOE_GAME_H
#define TICTACTOE_GAME_H
#include <vector>
#include "Player.h"


class Game {
private:
    std::vector<std::vector<char>> board;
    Player* currentPlayer;
    std::vector<Player*> playerVec;

public:
    Game();
    void displayBoard();
    bool initPlayers();
    void resetGame();
    bool makeMove(const int row, const int col);
    bool checkWin();
    bool isDraw();
    void switchPlayer();
    Player* getCurrentPlayer();
    void freeGame();
};


#endif //TICTACTOE_GAME_H
