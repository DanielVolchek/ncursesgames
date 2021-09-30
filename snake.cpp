//File name:/home/danielvolchek/snake/snake.cpp
//Daniel Volchek

//Code: Snake
#include <iostream>
#include <vector> // Coordinates
#include <stdio.h> // NULL
#include <ncurses.h> // g++ -l ncurses
#include <stdlib.h> // RAND 
#include <time.h> // RAND SEED
#include "getinput.h" // input header
using namespace std;
//snake length
int snakeLen;
//Screen Size
int screenY;
int screenX;
//Coordinates
int snakeTailCoord[2] = {-1,-1}; // Start declared as non existent
int snakeHeadCoord[2] = {-1,-1};
int snakeTurnCoord[2] = {-1, -1};
int appleCoord[2] = {-1,-1};
//Turn Vector and last turned
//Vector<int[2]> turnCoords;
int lastTurn; // Defined with KEY_UP KEY_DOWN etc...
//QUIT bool
bool QUIT;
//Apple eaten bool
bool ateApple;
//function decleration
void initScreen();
void initBoard(int** board);
void doLogic(int move);
void drawScreen(int** board);
void runGame();

int main(){
    srand(time(NULL)); // Rand Gen
    initScreen(); // start with init screen
    int**board {new int*[screenX]}; // Pointer to pointer array
    initBoard(board);
    drawScreen(board);
    QUIT = false;
    while (!QUIT){
        int c = getInput();
        if (c == KEY_RESIZE){
            endwin();
            initScreen();
            initBoard(board);
        }
        //doLogic(1);
        //drawScreen(board);
    }
    endwin();
    return 0;
}

void initScreen(){
    if (stdscr != NULL){ // If called on resize
        erase();
        endwin();
    }
    // standard functions
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true); // Enables keypad input
    start_color();
    refresh();
    getmaxyx(stdscr, screenY, screenX); // Assigns screen size variables
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
    if (ateApple){
        int appleCoord[2]={rand() % screenX-1, rand() % screenY-1};
        ateApple = false;
        snakeLen += 1;
    }
    if (move != lastTurn){ 
        switch(move){
            case KEY_UP:
                snakeHeadCoord[0] += 1;
                break;
            case KEY_DOWN:
                snakeHeadCoord[0] -= 1;
                break;
            case KEY_LEFT:
                snakeHeadCoord[1] -= 1;
                break;
            case KEY_RIGHT:
                snakeHeadCoord[1] += 1;
                break;
            case QUIT_CASE:
                QUIT = true;
                break;
            default:
            break;
        }
        //TODO: figure out vector solution for coordinates turnCoords.push_back(snakeHeadCoord)
    }
    if (snakeHeadCoord[0] == screenX || snakeHeadCoord[1] == screenY) // If 
        QUIT = true;
    if (snakeHeadCoord[0] == appleCoord[0] && snakeHeadCoord[1] == appleCoord[1]){
        ateApple = true;
    }
}
void drawScreen(int **board){
    for (int i = 0; i < screenX; i++){
        for (int j = 0; j < screenY; j++){
            move(j, i);
            if (board[i][j] == 1) 
                printw("x");
            else
                printw("%d", (board[i][j]));
            refresh();
        }
    }
}


