//File name:/home/danielvolchek/ncursesgames/main.cpp
//Daniel Volchek
//Selection menu to run games

//Code:

//Includes
#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

#define ENTER 10

ofstream fout; // err file
int screenX; // Screen X length
int screenY; // Screen Y length
//Function decleration
void runExec(char* exec_file);
void initScreen();
void selectionLoop();
void endScreen();
void chooseGame(int c);

int main(){
    fout.open("errfile");
    initScreen();
    selectionLoop();
    return 0;
}

void initScreen(){
    //Initializes screen to display menu on
    fout << "Init Screen" << endl;
    if (stdscr != NULL){ // If called on resize
        fout << "Resize called" << endl;
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
    fout << "Screen X: " << screenX << " Screen Y: " << screenY << endl;
}
void endScreen(){
    endwin();
}
void selectionLoop(){
    mvprintw(10, 0, "1");
    mvprintw(10, 5, "2");
    mvprintw(10, 10, "3");
    refresh();
    move (10, 0);
    int c;
    int position = 0;
    while (1){
        c = getch();
        fout << "c: " << c << endl;
        if (c == 'q')
            break;
        if (c == KEY_LEFT){
            fout << "KEY_LEFT" << endl;
            fout << "Position: " << position << endl;
            position -= 5;
            if (position < 0)
                position = 0;
            move(10, position);
            fout << "New Position: " << position << endl;
        }
        if (c == KEY_RIGHT){
            fout << "KEY_RIGHT" << endl;
            fout << "Position: " << position << endl;
            position += 5;
            if (position > 10)
                position = 10;
            move(10, position);
            fout << "New position: " << position << endl;
        }
        if (c == ENTER){
            fout << "KEY_ENTER " << endl;
            fout << "Position : " << position << endl;
            if (position == 0)
                chooseGame(1);
            if (position == 5)
                chooseGame(2);
            if (position == 10)
                chooseGame(3);
            wait(NULL);
        }
        refresh();
    }
    fout << "Exit loop" << endl;
    endwin();
}
void chooseGame(int c){
    endwin();
    fout << "Choose game " << c << endl;
    string filename;
    if (c == 1)
        filename = "./.pong";
    else if (c == 2)
        filename = "./.snake";
    else if (c == 3)
        filename = "./.conway";
    fout << "run exec " << filename;
    runExec(&filename[0]);
}
void runExec(char* exec_file){
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0){
       char* args[] = {exec_file, NULL}; 
       execvp(args[0], args);
    }
}
