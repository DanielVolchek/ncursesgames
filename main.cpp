//File name:/home/danielvolchek/ncursesgames/main.cpp
//Daniel Volchek
//Selection menu to run games

//Code:

#include "includes.h"
using namespace std;

#define ENTER 10
#define NUM_GAMES 4
ofstream fout; // err file
int screenX; // Screen X length
int screenY; // Screen Y length 
//Function decleration

int main(){
    const char *games[NUM_GAMES] = {"PONG", "GoL", "SNAKE", "INFO"};
    fout.open("errfile");
    initScreen();
    drawTitle();
    drawNames(games, 0);
    drawTODO();
    selectionLoop(games);
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
    curs_set(0);
    cbreak();
    keypad(stdscr, true); // Enables keypad input
    start_color();
    refresh();
    getmaxyx(stdscr, screenY, screenX); // Assigns screen size variables
    fout << "Screen X: " << screenX << " Screen Y: " << screenY << endl;
}
void drawTitle(){
    string title = "_  _ ____++ _  _ ____ ____ ____ ____    ____ ____ _  _ ____ ____ \n|\\ | |      |  | |__/ [__  |___ [__     | __ |__| |\\/| |___ [__  \n| \\| |___   |__| |  \\ ___] |___ ___]    |__] |  | |  | |___ ___]\n";
    string app = string(64, '-');
    title.append(app);
    int sLen = title.length();
    int printY = 1;
    int incX;
    int xContainer;
    for (int i = 0; i < sLen; i++){
        if (title.at(i) == '\n'){
            incX = screenX/2 - (i/2);
            xContainer = incX;
            break;
        }
    }
    for (int i = 0; i < sLen; i++){
        mvprintw(printY, incX++, "%c", title.at(i));
        if (title.at(i) == '\n'){
            printY++;
            incX = xContainer;
        }

    }

}
void drawNames(const char **games, int highlight){
    int increment = NUM_GAMES + 2;
    int y = screenY/2;
    int x = screenX/increment;
    if (highlight == 0)
        attron(A_REVERSE);
    mvprintw(y, x, games[0]);
    attroff(A_REVERSE);
    for (int i = 1; i < NUM_GAMES; i++){
        int len = sizeof(games[i-1]) / sizeof(games[i-1][0]);
        if (i == highlight)
            attron(A_REVERSE);
        mvprintw(y, x+len+(screenX/increment), games[i]);
        attroff(A_REVERSE);
        x += (screenX/increment)+len;
    }
}
void selectionLoop(const char **games){
    int c;
    int position = 0;
    while (1){
        c = getch();
        fout << "c: " << c << endl;
        if (c == 'q')
            break;
        if (c == KEY_RESIZE){            
            initScreen();
            drawTitle();
            drawNames(games, position);
        }
        if (c == KEY_LEFT){
            position--;
            if (position < 0)
                position = 0;
            drawNames(games, position);  
        }
        if (c == KEY_RIGHT){
            position++;
            if (position > NUM_GAMES-1)
                position = NUM_GAMES-1;
            drawNames(games, position);
        }
        if (c == ENTER){
            fout << "enter" << endl;
            fout << "position = " << position << endl;
            fout << "pos 3 = " << games[position] << endl;
            if (strncmp(games[position], "INFO", 4) == 0){
                fout << "show info called" << endl;
                showInfo();
                drawTitle();
                drawNames(games, position);
            }
            else{
                chooseGame(position);
                wait(NULL);
            }
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
    if (c == 0)
        filename = "./.pong";
    else if (c == 1)
        filename = "./.conway";
    else if (c == 2)
        filename = "./.snake";
    fout << "run exec " << filename;
    runExec(&filename[0]);
}
void showInfo(){
    clear();
    mvprintw(0, 0, "Pong: ");
    mvprintw(1, 0, "Play the world famous pong, first video game ever made (WIP)");
    mvprintw(2, 0, "Conway's Game of Life: ");
    mvprintw(3, 0, "Play Conway's Game of Life, complete with commands to provide enhanced utilities for the original Zero Player Game (WIP)");
    mvprintw(4, 0, "Snake: ");
    mvprintw(5, 0, "Play Snake, and eat every apple in sight, but don't touch those red walls!(WIP)");
    mvprintw(6, 0, "Press q to go back to selection");
    refresh();
    int c;
    while (c != 'q'){
        c = getch();
    }
    clear();    

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
void drawTODO(){
    int startLine = 25;
    mvprintw(startLine++, 0, "TODO:");
    mvprintw(startLine++, 0, "Add commands in GoL (file commands and mem commands)");
    mvprintw(startLine++, 0, "Fix pong physics");
    mvprintw(startLine++, 0, "Work through bugs in compiler output");
    mvprintw(startLine++, 0, "Add minimum size check to menu");
    mvprintw(startLine++, 0, "Remove todo function");
    mvprintw(startLine++, 0, "That's it! (for now)");
    refresh();
}
