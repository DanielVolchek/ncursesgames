//DANIEL VOLCHEK-NCURSES_GAMES_SNAKE
//Includes
#ifndef SNAKE_H
#define SNAKE_H
using namespace std;
#include "includes.h"
//Defines
#define EMPTY 0
#define WALL 1
#define SNAKE 2
#define APPLE 3
#define QUIT_CASE 10
#define KEY_ESC 27
//function decleration
namespace snake{
void initScreen();
void initBoard(int** board); 
void doLogic(int** board, int move); 
void drawInitScreen(int** board);
void runGame();
void pauseScreen(); //TODO
void getErrFile();
}
#endif
