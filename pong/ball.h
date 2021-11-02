//File name:/home/danielvolchek/ncursesgames/pong/ball.h
//Daniel Volchek
//Section_01

//Code:
#include <iostream>
using namespace std;
class ball{
    private:
    public:
        const char shape = 'o'; 
        int x;
        int y;
        int vx;
        int vy;
        void initBall(int screenY, int screenX, int dir){
            x = screenX/2;
            y = screenY/2;
        }
};
