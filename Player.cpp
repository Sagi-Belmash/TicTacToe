//
// Created by sagib on 23/01/2025.
//

#include <iostream>
#include <vector>
#include "Player.h"


static int player = 1;

Player::Player() : score(0) {
    getNameFromUser();
}

int Player::getScore() {
    return score;
}

void Player::incrementScore() {
    score++;
}

void Player::setPlayerNum(const int num) {
    playerNum = num;
    sign = playerNum ? 'O' : 'X';
}

int Player::getPlayerNum() {
    return playerNum;
}

void Player::getNameFromUser() {
    std::cout << "Player " << player++ << ", Enter your name:\n";
    std::cin >> name;
}

std::string Player::getName() {
    return name;
}

char Player::getSign() {
    return sign;
}


