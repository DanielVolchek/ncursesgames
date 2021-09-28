//File name:/home/danielvolchek/snake/snake.cpp
//Daniel Volchek

//Code: Snake
#include <iostream>
#include <ncurses.h> // g++ -l ncurses
using namespace std;

//variable decleration
//Directions
bool LEFT;
bool RIGHT;
bool UP;
bool DOWN;
//Screen Size
int screenY;
int screenX;
//Board Var

//function decleration
void initScreen();
void initBoard(int board[][]);
void logic();
void drawScreen(int board[][]);
void runGame();
void getInput();

int main(){
    int board[][];
    initBoard(board);
    initScreen();
    drawScreen(board);
    getInput();
    //while (true){
    //    getInput();
    //}
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
    //WINDOW *snakeWin = stdscr;//newwin(screenY/2, screenX/2, screenY/4, screenX/4); // Snake wil be drawn in this window
    box(stdscr, 0, 0);
    wgetch(stdscr);
}
void initBoard(int board[][]){
    for (int i = 0; i < screenX; i++){
        for (int j = 0; j < screenY; j++){
            if (i == 0 || j == 0){
                board[i][j] = -1;
            }
            else board[i][j] = 0;
        }
    }
}
void drawScreen(int board[][]){
    for (int i = 0; i < screenX; i++){
        for (int j = 0; j < screenY; j++){
            printw("%d", (board[i][j]));
        }
        printw("\n");
    }

}
void getInput(){
        {
        int c = getch();
        switch (c){
            case KEY_RESIZE: // Catch resize
            initScreen();
            break;
            case KEY_UP:
            UP = true;
            break;
            case KEY_LEFT:
            LEFT = true;
            break;
            case KEY_RIGHT:
            RIGHT = true;
            break;
            case KEY_DOWN:
            DOWN = true;
            break;
            case 'w':
            UP = true;
            break;
            case 'a':
            LEFT = true;
            break;
            case 'd':
            RIGHT = true;
            break;
            case 's':
            DOWN = true;
            break;
            case 'q':
            endwin();
            exit(1);
            default:
            break;
        }
    }
}
