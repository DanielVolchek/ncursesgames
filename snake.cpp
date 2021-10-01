//DANIEL VOLCHEK-NCURSES_GAMES_SNAKE
//Includes
#include <iostream>
#include <vector> // Coordinates
#include <tuple> // Coords for Vector
#include <stdio.h> // NULL
#include <ncurses.h> // g++ -l ncurses
#include <stdlib.h> // RAND 
#include <time.h> // RAND SEED
#include <fstream> //Err checking
#include <string> // File Checking
#include "getinput.h" // input header
using namespace std;

//Defines
#define EMPTY 0
#define WALL 1
#define SNAKE 2
#define APPLE 3
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
vector<tuple<int,int,int>> turnCoords;
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
void pauseScreen(); //TODO
void getErrFile();

//TODO Fix apple placement after eat
//TODO Add constant direction (continous same key until new key detected
//TODO Deal with length
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
        else if (c == 'q'){
            fout << "QUIT" << endl;
            endwin();
            break;
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
    //Color Pairs
    init_pair(WALL, COLOR_BLACK, COLOR_RED);
    init_pair(APPLE, COLOR_GREEN, COLOR_BLACK);
    init_pair(SNAKE, COLOR_BLUE, COLOR_BLACK);
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
    snakeTailCoord[0] = snakeHeadCoord[0]-1;
    snakeTailCoord[1] = snakeTailCoord[1];
    board[snakeTailCoord[0]][snakeTailCoord[1]] = SNAKE;
    fout << "Snake set at " << snakeHeadCoord[0] << "," << snakeHeadCoord[1] << endl;
    fout << "Set Apple" << endl;
    board[rand() % screenX-2][rand() % screenY-2] = APPLE;
    //TODO Generate walls
}
void doLogic(int **board, int move){
    fout << "Do Logic" << endl;
    fout << "move is " << move << endl; 
    fout << "Apple set" << endl;
    fout <<"move is " << move << " last turn is " << lastTurn << endl;
    fout <<"snake head coord is " << snakeHeadCoord[0] << "," << snakeHeadCoord[1] << endl; 
    fout << "Move is: " << move << endl;
    
    if (lastTurn != move){
        fout << "add move to turn coords, (" << snakeHeadCoord[0] << "," << snakeHeadCoord[1] << "," << move << ")" << endl; 
        turnCoords.push_back(make_tuple(snakeHeadCoord[0], snakeHeadCoord[1], move));
        fout << "move added" << endl;
    }
    //Head
    switch(move){
        case KEY_UP:
            snakeHeadCoord[1] -= 1;
            break;
        case KEY_DOWN:
            snakeHeadCoord[1] += 1;
            break;
        case KEY_LEFT:
            snakeHeadCoord[0] -= 1;
            break;
        case KEY_RIGHT:
            snakeHeadCoord[0] += 1;
            break;
    }
    //Tail
    tuple<int,int,int> tc = turnCoords.front();
    int turnDir = get<2>(tc);
    fout << "enter switch statement" << endl;
    fout << "turn dir " << turnDir << endl;
    fout << "KEY_UP: " << KEY_UP << endl;
    fout << "KEY_DOWN: " << KEY_DOWN << endl;
    fout << "KEY_LEFT: " << KEY_LEFT << endl;
    fout << "KEY_RIGHT: " << KEY_RIGHT << endl;
    fout << "snake tail 0 " << snakeTailCoord[0] << endl;
    fout << "snake tail 1 " << snakeTailCoord[1] << endl;

    switch(turnDir){
        case KEY_UP:
            snakeTailCoord[1] -= 1;
            fout << "set snake tail" << endl;
            board[snakeTailCoord[0]][snakeTailCoord[1]+1] = 0;
            break;
        case KEY_DOWN:
            snakeTailCoord[1] += 1;
            board[snakeTailCoord[0]][snakeTailCoord[1]-1] = 0;
            break;
        case KEY_LEFT:
            snakeTailCoord[0] -= 1;
            board[snakeTailCoord[0]+1][snakeTailCoord[1]] = 0;
            break;
        case KEY_RIGHT:
            snakeTailCoord[0] += 1;
            board[snakeTailCoord[0]-1][snakeTailCoord[1]] = 0;
            break;
    }
    fout << "add tail to snake" << endl;
    board[snakeTailCoord[0]][snakeTailCoord[1]] = SNAKE;
    if (snakeTailCoord[0] == get<0>(tc) && snakeTailCoord[1] == get<1>(tc)){
        fout << "snake hit turn" << endl;
        turnCoords.erase(turnCoords.begin());
    }
    fout << "check if hit obstacle" << endl;
    if (board[snakeHeadCoord[0]][snakeHeadCoord[1]] == WALL || board[snakeHeadCoord[0]][snakeHeadCoord[1]] == SNAKE){ // If hit obstacle
        fout << "hit obstacle at " << snakeHeadCoord[0] << "," << snakeHeadCoord[1] << endl;
        QUIT = true;
    }
    fout << "check ate apple" << endl;
    if (board[snakeHeadCoord[0]][snakeHeadCoord[1]] == APPLE){
        fout << "New Apple" << endl;
        appleCoord[0] = rand() % screenX-1;
        appleCoord[1] = rand() % screenY-1;
        fout << "Apple at: " << appleCoord[0] << "," << appleCoord[1] << endl;
        board[appleCoord[0]][appleCoord[1]] = APPLE;
        ateApple = false;
        snakeLen += 1;
        switch(turnDir){
            case KEY_UP:
                snakeTailCoord[0] -= 1;
                board[snakeTailCoord[0]][snakeTailCoord[1]+1] = 0;
                break;
            case KEY_DOWN:
                snakeTailCoord[0] += 1;
                board[snakeTailCoord[0]][snakeTailCoord[1]-1] = 0;
                break;
            case KEY_LEFT:
                snakeTailCoord[1] -= 1;
                board[snakeTailCoord[0]+1][snakeTailCoord[1]] = 0;
                break;
            case KEY_RIGHT:
                snakeTailCoord[1] += 1;
                board[snakeTailCoord[0]-1][snakeTailCoord[1]] = 0;
                break;
        }
    }
    fout << "set head to snake" << endl;
    board[snakeHeadCoord[0]][snakeHeadCoord[1]] = SNAKE;
}
void drawScreen(int** board){
    for (int x = 0; x < screenX; x++){
        for (int y = 0; y < screenY; y++){
            //fout << "\toutput at" << x << "," << y << endl;
            move(y, x);
            if (board[x][y] == WALL){
                attron(COLOR_PAIR(WALL));
                printw("x");
                attroff(COLOR_PAIR(WALL));
            }
            else if (board[x][y] == APPLE){
                attron(COLOR_PAIR(APPLE));
                printw("0");
                attroff(COLOR_PAIR(APPLE));
            }
            else if (board[x][y] == SNAKE){
                attron(COLOR_PAIR(SNAKE));
                printw("0");
                attroff(COLOR_PAIR(SNAKE));
            }
            else
                printw("%d", (board[x][y]));
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
    cout << errFileName << endl; //For input piping to cat './game | xargs cat'
    fout.open(errFileName); // Open fout
    errFileIn.close();
    ofstream errFileOut;
    errFileOut.open("errfiles/filecount", ios::in | ios::trunc); // Open filecount to output new file number
    errFileOut << n;
    errFileOut.close();
}
