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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ball.h"
#include "paddle.h"
#include "bubble.h"

#define QUIT_CASE 10
#define SLOW_DOWN_MS 50 
#define KEY_ESC 27
#define PLAYER_ONE 1
#define PLAYER_TWO 2
using namespace std;
namespace pong{
void runGame();
void endGame(bool win);
void clearPaddle(paddle *p);
bool checkBallHit();
void initBall();
void incrementBall();
void drawMid();
void drawScore();
void drawScreen();
void movePaddles(paddle* p, int direction, int *lastMove);
void doCPUMove();
void initPaddles();
void drawPaddles();
void initScreen();
void resizeScreen();
int getInput();
}
