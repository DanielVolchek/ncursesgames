//File name:/home/danielvolchek/snake/snake.cpp
//Daniel Volchek

//Code: Snake
#include <iostream>
#include <ncurses.h> // g++ -l ncurses
using namespace std;

#define UP_KEY 38
#define LEFT_KEY 37
#define RIGHT_KEY 39
#define DOWN_KEY 40
#define ENTER_KEY 13
void initScreen();
void logic();
void drawScreen();
void runGame();
void getInput();

int main(){
    initScreen();
    getInput();   
    return 0;
}

void initScreen(){
    initscr();
    noecho();
    raw();

}
void getInput(){
    char c = _getch();
    bool running = true;
    while (running){
        switch (c){
            case 'w': printw("west"); break;
            case UP_KEY: printw("west"); break;
            case 'q': running = false; break;
        }
    }
    endwin();

}
