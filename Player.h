//
// Created by sagib on 23/01/2025.
//

#ifndef TICTACTOE_PLAYER_H
#define TICTACTOE_PLAYER_H
#include <string>


class Player {
private:
    std::string name;
    int score;
    int sign;
    int playerNum;
public:
    Player();
    int getScore();
    void incrementScore();
    void setPlayerNum(const int num);
    int getPlayerNum();
    void getNameFromUser();
    std::string getName();
    char getSign();
};


#endif //TICTACTOE_PLAYER_H
