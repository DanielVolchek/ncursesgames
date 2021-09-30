//File name:/home/danielvolchek/snake/snake.cpp
//Daniel Volchek

//Code: Snake
#include <iostream>
#include <ncurses.h> // g++ -l ncurses
#include <stdlib.h> // RAND 
#include <time.h> // RAND SEED
#include "getinput.h" // input header
using namespace std;

//Screen Size
int screenY;
int screenX;
//Board Var

//function decleration
void initScreen();
void initBoard(int** board);
void doLogic(int move);
void drawScreen(int** board);
void runGame();

int main(){
    initScreen();
    int**board {new int*[screenX]};
    endwin();
    initBoard(board);
    drawScreen(board);
    while (true){
        int c = getInput();
        if (c == KEY_RESIZE){
            endwin();
            initScreen();
            initBoard(board);
        }
        if (c == QUIT_CASE)
            break;
        doLogic(1);
        drawScreen(board);
    }
    endwin();
    return 0;
}

void initScreen(){
    if (stdscr != NULL){ // If called on resize
        erase();
        endwin();
    }
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true); // Enables keypad input
    refresh();
    getmaxyx(stdscr, screenY, screenX);
}
void initBoard(int **board){
    for (int i = 0; i < screenX; i++){
        board[i] = new int[screenY];
    }
    for (int i = 0; i < screenX; i++){
        for (int j = 0; j < screenY; j++){
            if (i == 0 || j == 0 || i == screenX-1 || j == screenY-1){
                board[i][j] = 1;
            }
            else board[i][j] = 0;
        }
    }
}
void doLogic(int move){
    
}
void drawScreen(int **board){
    for (int i = 0; i < screenX; i++){
        for (int j = 0; j < screenY; j++){
            move(j, i);
            printw("%d", board[i][j]);
            refresh();
        }
    }
}


