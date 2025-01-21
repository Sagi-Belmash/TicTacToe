//
// Created by sagib on 21/01/2025.
//

#ifndef TICTACTOE_GAME_H
#define TICTACTOE_GAME_H
#include <vector>


class Game {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;

public:
    Game();
    void displayBoard();
    bool makeMove(const int row, const int col);
    bool checkWin();
    bool isDraw();
    void switchPlayer();
    char getCurrentPlayer();
};


#endif //TICTACTOE_GAME_H
