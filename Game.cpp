//
// Created by sagib on 21/01/2025.
//
#include <iostream>
#include "Game.h"
#define ROW_SEP "-------------\n"

Game::Game() : board(3, std::vector<char>(3, ' ')) {
    playerVec.reserve(2 * sizeof(Player*));
    initPlayers();
    std::srand(time(0));
}

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

bool Game::initPlayers() {
    try {
        Player* p1 = new Player();
        Player* p2 = new Player();
        playerVec.push_back(p1);
        playerVec.push_back(p2);
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << '\n';
        return false;
    }
    return true;
}

void Game::resetGame() {
    playerVec[0]->setPlayerNum(std::rand() % 2);
    playerVec[1]->setPlayerNum(1 - playerVec[0]->getPlayerNum());
    currentPlayer = playerVec[0]->getPlayerNum() == 0 ? playerVec[0] : playerVec[1];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
    std::cout << "Current scores:\n" << playerVec[0]->getName() << ": " << playerVec[0]->getScore() << " | " << playerVec[1]->getName() << ": " << playerVec[1]->getScore() << "\n";
}

bool Game::makeMove(const int row, const int col) {
    if (row >= 0 && row <= 2 && col >= 0 && col <= 2 && board[row][col] == ' ') {
        board[row][col] = getCurrentPlayer()->getSign();
        return true;
    }
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
    currentPlayer = currentPlayer->getPlayerNum() == playerVec[0]->getPlayerNum() ? playerVec[1] : playerVec[0];
}

Player* Game::getCurrentPlayer() {
    return currentPlayer;
}

void Game::freeGame() {
    for (Player* pP : playerVec) {
        delete(pP);
    }
    playerVec.clear();
}

