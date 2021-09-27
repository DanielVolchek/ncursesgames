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
    int board[][];

//function decleration
    void initScreen();
    void initBoard();
    void logic();
    void drawScreen();
    void runGame();
    void getInput();

int main(){
    initScreen();
    while (true){
        getinput();
    }
    return 0;
}

void initScreen(){
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true); // Enables keypad input
    refresh();
    getmaxyx(stdscr, screenY, screenX);
    Window *snakeWin = newwin(screenY/2, screenX/2, screenY/4, screenX/4); // Snake wil be drawn in this window
    box(snakeWin, 0, 0);
    wgetch(snakeWin);
}
void initBoard(){
    
}
void getInput(){
    if (kbhit()){
        int c = getch();
        switch (c){
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
        }
    }
}
