//File name:/home/danielvolchek/ncursesgames/pong/pong.cpp
//Daniel Volchek
//Section_01

//Code:
#include <iostream>
#include <ncurses.h>
#include <tuple>
#include <thread>
#include <chrono>
#include <fstream>
#include "ball.h"
#include "paddle.h"
#define QUIT_CASE -10
#define SLOW_DOWN_MS 50 
#define KEY_ESC 27
using namespace std;

ofstream fout;
int screenY;
int screenX;
paddle paddleOne;
paddle paddleTwo;
ball ballOne;
int score1;
int score2;

void runGame();
bool checkBallHit();
void initBall();
void incrementBall();
void drawMid();
void drawScreen();
void movePaddles(int direction);
void initPaddles();
void drawPaddles();
void initScreen();
void resizeScreen();
int getInput();

int main(){
    fout.open("errfile");
    runGame();
    return 0;
}

void initScreen(){
    fout << "Init Screen" << endl;
    if (stdscr != NULL){ // If called on resize
        fout << "Resize called" << endl;
        erase();
        endwin();
    }
    // standard functions
    initscr();
    curs_set(0); // Remove cursor
    noecho();
    cbreak();
    keypad(stdscr, true); // Enables keypad input
    nodelay(stdscr, true);
    start_color();
    refresh();
    getmaxyx(stdscr, screenY, screenX); // Assigns screen size variables
    fout << "Screen X: " << screenX << " Screen Y: " << screenY << endl;
 
}
void runGame(){
    initScreen();
    initPaddles();
    initBall();
    drawScreen();
    int c;
    while (1){
        c = getInput();
        if (c == QUIT_CASE){
            break;
        }
        if (c == KEY_ESC){
            while(true){
                c = getInput();
                if (c == KEY_ESC){
                    break;
                }
                if (c == QUIT_CASE){
                    goto stop;
                }
            }
        }  
        if (c != 0 || c != KEY_ESC){
            movePaddles(c);
        }
        incrementBall();
        drawScreen();
    }
    stop: 
    endwin();
}
void initPaddles(){
    // Paddles should be one fifth of the vertical length
    //TODO
    paddleOne.length = screenY / 5;
    paddleTwo.length = screenY / 5; //screenY5;
    paddleOne.setCoord(0, screenY/2-(paddleOne.length/2));
    paddleTwo.setCoord(screenX-1, screenY/2-(paddleOne.length/2));
}
void initBall(){
    double speedPercent = ballOne.y / paddleOne.y;
    ballOne.x = screenX/2;
    ballOne.y = screenY/2;
    ballOne.vx = -1;
    ballOne.vy = 1;
}
void movePaddles(int direction){
    //TODO modify to get passed in paddle
    flushinp();
    int paddleYMove = paddleOne.y + direction;
    if (paddleYMove+paddleOne.length > screenY || paddleYMove < 0)
        return;
    if (direction == 1){
        for (int i = 0; i < paddleOne.width; i++){
            mvprintw(paddleOne.y, paddleOne.x + i, " ");
        }
    }
    else{
        for (int i = 0; i < paddleOne.width; i++){
            mvprintw(paddleOne.y+paddleOne.length-1, paddleOne.x + i, " ");
        }
    }
    paddleOne.setCoord(0, paddleYMove);
   

}
void incrementBall(){
    int moveX = ballOne.x + ballOne.vx;
    int moveY = ballOne.y + ballOne.vy;
    mvprintw(ballOne.y, ballOne.x, " ");
    if (moveX < 0){
       paddleTwo.score++;
       initBall();
    }
    else if (moveX >= screenX){
        paddleOne.score++;
        initBall();
    }
    else{
        ballOne.x = moveX;
    }
    if (moveY < 0){
        ballOne.y = 0;
        ballOne.vy = -ballOne.vy;
    } 
    else if (moveY >= screenY){
        ballOne.y = screenY-1;
        ballOne.vy = -ballOne.vy;
    }
    else{
        ballOne.y = moveY;
    }
    if (checkBallHit()){
        //TODO speed modification
        ballOne.vx = -ballOne.vx;
        //ballOne.vy = -ballOne.vy;
    }
}
bool checkBallHit(){
    bool ballBetweenX = (ballOne.x >= paddleOne.x && ballOne.x <= paddleOne.x + paddleOne.width) || 
    (ballOne.x <= paddleTwo.x && ballOne.x >= paddleTwo.x - paddleOne.width);
    bool ballBetweenY = (ballOne.y >= paddleOne.y && ballOne.y <= paddleOne.y + paddleOne.length) ||
    (ballOne.y >= paddleTwo.y && ballOne.y <= paddleTwo.y + paddleOne.length);
    bool ballHitSide = (ballOne.x >= paddleOne.x && ballOne.x <= paddleOne.width && (ballOne.y == paddleOne.x || ballOne.y == paddleOne.x + paddleOne.length)) ||
    (ballOne.x >= paddleTwo.x && ballOne.x <= paddleTwo.width && (ballOne.y == paddleTwo.x || ballOne.y == paddleTwo.x + paddleTwo.length)); 
    return (ballBetweenX && ballBetweenY) || ballHitSide;
}
int getInput(){
    int c = getch();
    switch (c){
        case KEY_UP: return -1;
        case KEY_DOWN: return 1;
        case KEY_ESC: return KEY_ESC;
        case 'q': return QUIT_CASE;
        default: return 0;
    }
}
void drawPaddles(){
    for (int i = 0; i < paddleOne.length; i++){
        for (int j = 0; j < paddleOne.width; j++){
            mvprintw(paddleOne.y + i, j, "|");
            mvprintw(paddleTwo.y + i, paddleTwo.x - j, "|");
        }
    }
}

void drawBall(){
   mvprintw(ballOne.y, ballOne.x, "o"); 
}
void drawMid(){
    for (int i = 0; i < screenY; i+=2){
        mvprintw(i, screenX/2, "|");
    }
}
void drawScreen(){
    drawPaddles();
    drawMid();
    drawBall();
    refresh();
    this_thread::sleep_for(chrono::milliseconds(SLOW_DOWN_MS));
}
