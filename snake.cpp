//File name:/home/danielvolchek/snake/snake.cpp
//Daniel Volchek

//Code: Snake
#include <iostream>
#include <ncurses.h> // g++ -l ncurses
#include "getinput.h"
using namespace std;

//variable decleration
//Directions

bool LEFT;
bool RIGHT;
bool UP;
bool DOWN;
bool QUIT;
bool RESIZE;

//Screen Size
int screenY;
int screenX;
//Board Var

//function decleration
void initScreen();
void initBoard(int** board);
void doLogic();
void drawScreen(int** board);
void runGame();

int main(){
    initScreen();
    int**board {new int*[screenX]};
    initBoard(board);
    drawScreen(board);
    while (!QUIT){
        getInput(&UP, &DOWN, &LEFT, &RIGHT, &QUIT, &RESIZE);
        if (RESIZE){
            endwin();
            RESIZE = false;
            initScreen();

        }
        //doLogic();
        drawScreen(board);
    }
    endwin();
    return 0;
}

void initScreen(){
    /*if (stdscr != NULL){ // If called on resize
        erase();
        endwin();
    }
    */
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true); // Enables keypad input
    refresh();
    getmaxyx(stdscr, screenY, screenX);
    //WINDOW *snakeWin = stdscr;//newwin(screenY/2, screenX/2, screenY/4, screenX/4); // Snake wil be drawn in this window
    box(stdscr, 0, 0);
    wgetch(stdscr);
}
void initBoard(int **board){
    for (int i = 0; i < screenX; i++){
        board[i] = new int[screenY];
    }
    for (int i = 0; i < screenX; i++){
        for (int j = 0; j < screenY; j++){
            if (i == 0 || j == 0 || i == screenX-1 || j == screenX-1){
                board[i][j] = 1;
            }
            else board[i][j] = 0;
        }
    }
}
void drawScreen(int **board){
    for (int i = 0; i < screenX; i++){
        for (int j = 0; j < screenY; j++){
            move(j, i);
            printw("%d",board[screenX][screenY]);
        }
    }

}

