//
// Created by sagib on 21/01/2025.
//
#include <iostream>
#include "Game.h"
#include "main.h"

#define GAME_START "==============================\n=====     GAME START     =====\n==============================\n"

int main() {
    Game game;
    bool gameOn = true;
    char playAgain;
    while (gameOn) {
        std::cout << GAME_START;
        game.resetGame();
        game.displayBoard();
        while (true) {
            std::cout << game.getCurrentPlayer()->getName() << "! It's your turn!\n";
            int row;
            int col;
            while (true) {
                std::cout << "Enter row (0-2) and col (0-2):\n";
                std::cin >> row >> col;
                if (game.makeMove(row, col)) break;
                std::cout << "Place is invalid or occupied, please choose another\n";
            }
            game.displayBoard();
            if (game.checkWin()) {
                std::cout << "The winner is " << game.getCurrentPlayer()->getName() << "!\n";
                game.getCurrentPlayer()->incrementScore();
                break;
            }
            if (game.isDraw()) {
                std::cout << "It's a draw!\n";
                break;
            }
            game.switchPlayer();
        }
        std::cout << "Play again? (y/Y if yes, any other key to no)\n";
        std::cin >> playAgain;
        if (tolower(playAgain) != 'y')
            gameOn = false;
    }
    std::cout << "Bye bye!";
    game.freeGame();
    return 0;
}