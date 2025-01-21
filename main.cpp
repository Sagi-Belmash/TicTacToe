//
// Created by sagib on 21/01/2025.
//
#include <iostream>
#include "Game.h"

int main() {
    Game game;
    game.displayBoard();

    while (true) {
        std::cout << game.getCurrentPlayer() << "! It's your turn!\n";
        int row;
        int col;
        do {
            std::cout << "Enter row (0-2) and col (0-2):\n";
            std::cin >> row >> col;
        } while (!game.makeMove(row, col));
        game.displayBoard();
        if (game.checkWin()) {
            std::cout << "The winner is " << game.getCurrentPlayer() << "!\n";
            break;
        }
        if (game.isDraw()) {
            std::cout << "It's a draw!\n";
            break;
        }
        game.switchPlayer();
    }
    return 0;
}
