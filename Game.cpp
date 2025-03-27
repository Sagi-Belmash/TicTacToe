#include "Game.h"


Game::Game() {
    std::cout << "Game created" << std::endl;
}

Game::~Game() {
    std::cout << "Game destroyed" << std::endl;
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

// Resetes the symbol vectors
void Game::resetGame() {
    xVec.clear();
    oVec.clear();
    currPlayer = 'X';
}

// If possible, places the current symbol on the dessired row and column
bool Game::makeMove(int row, int col) {
    if (row >= 0 && row <= 2
        && col >= 0 && col <= 2
        && !std::count(xVec.begin(), xVec.end(), row * 3 + col)
        && !std::count(oVec.begin(), oVec.end(), row * 3 + col)) {
        std::vector<int>& currVec = currPlayer == 'X' ? xVec : oVec;
        currVec.push_back(row * 3 + col);
        return true;
    }
    return false;
}

// Return true if the current player has won
bool Game::checkWin(int* begin, int* end) {
    std::vector<int> currVec = currPlayer == 'X' ? xVec : oVec;
    int winArrs[][3] = {
        { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 },
        { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 },
        { 0, 4, 8 }, { 2, 4, 6}
    };

    if (currVec.size() >= 3) {
        for (int* winArr : winArrs) {
            if (std::count(currVec.begin(), currVec.end(), winArr[0]) &&
                std::count(currVec.begin(), currVec.end(), winArr[1]) &&
                std::count(currVec.begin(), currVec.end(), winArr[2])) {
                *begin = winArr[0];
                *end = winArr[2];
                return true;
            }
        }
    }
    return false;
}

void Game::switchPlayer() {
    currPlayer = currPlayer == 'X' ? 'O' : 'X';
}
// Returns the symbol of the current player
char Game::getCurrentPlayer() {
    return currPlayer;
}

