//File name:/home/danielvolchek/snake/snake.cpp
//Daniel Volchek

//Code: Snake
#define EMPTY 0
#define WALL 1
#define SNAKE 2
#define APPLE 3

#include <iostream>
#include <vector> // Coordinates
#include <stdio.h> // NULL
#include <ncurses.h> // g++ -l ncurses
#include <stdlib.h> // RAND 
#include <time.h> // RAND SEED
#include <fstream> //Err checking
#include <string>
#include "getinput.h" // input header
using namespace std;
//Err checking
ofstream fout;

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
void doLogic(int** board, int move); 
void drawScreen(int** board);
void runGame();
void getErrFile();
int main(){
    getErrFile();
    srand(time(NULL)); // Rand Gen
    initScreen(); // start with init screen
    int**board {new int*[screenX]}; // Pointer to pointer array
    initBoard(board);
    ateApple = true; // Set for first pass
    lastTurn = -1; // Set for first pass
    fout << "Draw Screen" << endl;
    drawScreen(board);
    QUIT = false;
    while (!QUIT){
        int c = getInput();
        if (c == KEY_RESIZE){
            fout << "Resize" << endl;
            endwin();
            initScreen();
            initBoard(board);
        }
        else doLogic(board, c);
        drawScreen(board);
    }
    endwin();
    return 0;
}

void initScreen(){
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
void initBoard(int** board){
    fout << "Init Board" << endl;
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
    // Set snake head in the middle of the screen
    snakeHeadCoord[0] = screenX/2;
    snakeHeadCoord[1] = screenY/2;
    board[snakeHeadCoord[0]][snakeHeadCoord[1]] = SNAKE;
    fout << "Snake set at " << snakeHeadCoord[0] << "," << snakeHeadCoord[1] << endl;
}
void doLogic(int **board, int move){
    fout << "Do Logic" << endl;
    fout << "move is " << move << endl;
    if (ateApple){
        fout << "New Apple" << endl;
        appleCoord[0] = rand() % screenX-1;
        appleCoord[1] = rand() % screenY-1;
        fout << "Apple at: " << appleCoord[0] << "," << appleCoord[1] << endl;
        ateApple = false;
        snakeLen += 1;
    }
    fout << "Set Apple" << endl;
    board[appleCoord[0]][appleCoord[1]] = APPLE;
    fout << "Apple set" << endl;
    fout <<"move is " << move << " last turn is " << lastTurn << endl;
    fout <<"snake head coord is " << snakeHeadCoord[0] << "," << snakeHeadCoord[1] << endl;
    if (move != lastTurn){ 
        fout << "Do Move" << endl;
        switch(move){
            case KEY_UP:
                snakeHeadCoord[0] -= 1;
                break;
            case KEY_DOWN:
                snakeHeadCoord[0] += 1;
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
        lastTurn = move;
        board[snakeHeadCoord[0]][snakeHeadCoord[1]] = SNAKE;
        //TODO: figure out vector solution for coordinates turnCoords.push_back(snakeHeadCoord)
    }
    else{
        fout << "Move = last move" << endl;
    }
    fout << "check quit" << endl;
    if (snakeHeadCoord[0] == screenX || snakeHeadCoord[1] == screenY) // If 
        QUIT = true;
    fout << "check ate apple" << endl;
    if (snakeHeadCoord[0] == appleCoord[0] && snakeHeadCoord[1] == appleCoord[1]){
        ateApple = true;
    }
}
void drawScreen(int** board){
    init_pair(WALL, COLOR_BLACK, COLOR_RED);
    init_pair(APPLE, COLOR_GREEN, COLOR_BLACK);
    init_pair(SNAKE, COLOR_BLUE, COLOR_BLACK);
    for (int i = 0; i < screenX; i++){
        for (int j = 0; j < screenY; j++){
            //fout << "\toutput at" << i << "," << j << endl;
            move(j, i);
            if (board[i][j] == WALL){
                attron(COLOR_PAIR(WALL));
                printw("x");
                attroff(COLOR_PAIR(WALL));
            }
            else if (board[i][j] == APPLE){
                attron(COLOR_PAIR(APPLE));
                printw("0");
                attroff(COLOR_PAIR(APPLE));
            }
            else if (board[i][j] == SNAKE){
                attron(COLOR_PAIR(SNAKE));
                printw("0");
                attroff(COLOR_PAIR(SNAKE));
            }
            else
                printw("%d", (board[i][j]));
            refresh();
        }
    }
}

void getErrFile(){
    // Open File to read from
    ifstream errFileIn;
    errFileIn.open("errfiles/filecount", ios::out); // Get file ending from filecount
    string s;
    getline(errFileIn, s); // Read in from filecount
    int n = stoi(s);
    n++; // Increment filecount by 1
    s = "errfiles/errfile";
    string errFileName = s.append(to_string(n)); // Set ErrFileName to errfile+n
    fout.open(errFileName); // Open fout
    errFileIn.close();
    ofstream errFileOut;
    errFileOut.open("errfiles/filecount", ios::in | ios::trunc); // Open filecount to output new file number
    errFileOut << n;
    errFileOut.close();
}
