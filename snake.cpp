//File name:/home/danielvolchek/snake/snake.cpp
//Daniel Volchek

//Code: Snake
#include <iostream>
#include <ncurses.h> // g++ -l ncurses
using namespace std;

#define UP_KEY 72
#define LEFT_KEY 75
#define RIGHT_KEY 77
#define DOWN_KEY 80

void initScreen();
void logic();
void drawScreen();
void runGame();
void getInput();

int main(){
    initScreen();
   
    return 0;
}

void initScreen(){
    initscr();



}
