//
// Created by sagib on 21/01/2025.
//
#include <iostream>
#include "Game.h"
#define ROW_SEP "-------------\n"

Game::Game() : board(3, std::vector<char>(3, ' ')), currentPlayer('X') {}

void Game::displayBoard() {
    for (const auto& row : board) {
        std::cout << ROW_SEP;
        for (const auto& cell : row) {
            std::cout << "| " << cell << " ";
        }
        std::cout << "|\n";
    }
    std::cout << ROW_SEP;
}

bool Game::makeMove(const int row, const int col) {
    if (row >= 0 && row <= 2 && col >= 0 && col <= 2 && board[row][col] == ' ') {
        board[row][col] = getCurrentPlayer();
        return true;
    }
    std::cout << "Place is invalid or occupied, please choose another\n";
    return false;
}

bool Game::checkWin() {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) ||
           (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i])) return true;
    }
    if ((board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) ||
       (board[2][0] != ' ' && board[2][0] == board[1][1] && board[2][0] == board[0][2])) return true;
    return false;
}

bool Game::isDraw() {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}

void Game::switchPlayer() {
    currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
}

char Game::getCurrentPlayer() {
    return currentPlayer;
}


