//File name:/home/danielvolchek/ncursesgames/pong/ball.h
//Daniel Volchek
//Section_01

//Code:

#include <iostream>
#ifndef BALL_H
#define BALL_H
using namespace std;
class ball{
    private:
    public:
        const char shape = 'o'; 
        int x;
        int y;
        int vx;
        int vy; 
};
#endif
