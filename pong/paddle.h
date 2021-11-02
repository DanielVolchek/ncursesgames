//File name:/home/danielvolchek/ncursesgames/pong/paddle.h
//Daniel Volchek
//Section_01

//Code:
#include <iostream>
using namespace std;
class paddle{
    public:
        int x;
        int y;
        int length;
        int width = 3;
        int score = 0;
        void setCoord(int moveX, int moveY);
};
