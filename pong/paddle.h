//File name:/home/danielvolchek/ncursesgames/pong/paddle.h
//Daniel Volchek
//Section_01

//Code:
#include <iostream>
#ifndef PADDLE_H
#define PADDLE_H
using namespace std;
class paddle{
    public:
        const int width = 3;
        int x;
        int y;
        int length;
        int score;
        int velocity;
        int max_velocity;
        void setCoord(int moveX, int moveY);
};
#endif
