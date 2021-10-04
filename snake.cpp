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
#include <unistd.h>// Sleep
#include "getinput.h" // input header
using namespace std;

// Vector of <int,int> snakecoords
// starts with two, snake head and snake tail
// increment each element every turn, then draws from them
// in draw, after initial for loop go in to vector for loop and draw on top of coord with move
// 

//Defines
#define EMPTY 0
#define WALL 1
#define SNAKE 2
#define APPLE 3
//Err checking
ofstream fout;
//snake length
int snakeLen = 3;
//Screen Size
int screenY;
int screenX;
//Coordinates
int snakeTailCoord[2] = {-1,-1}; // Start declared as non existent
int snakeHeadCoord[2] = {-1,-1};
int snakeTurnCoord[2] = {-1, -1};
int appleCoord[2] = {-1,-1};
//Turn Vector and last turned
vector<tuple<int,int,int,int, int>> turnCoords; // Before turn move, after turn move, coords where move happened, iterator of num snake parts gone through turn
vector<tuple<int,int,int>> snakeCoords;
int lastMove; // Defined with KEY_UP KEY_DOWN etc...
int turnCount = 0;
//QUIT bool
bool QUIT;
//Apple eaten bool
bool ateApple;
bool snakeHitTurn;
//function decleration
void initScreen();
void initBoard(int** board); 
void doLogic(int** board, int move); 
void doLogic(int** board, int move);
void drawScreen(int** board);
void runGame();
void pauseScreen(); //TODO
void getErrFile();

//TODO Add constant direction (continous same key until new key detected
//TODO Deal with length
int main(){
    getErrFile();
    srand(time(NULL)); // Rand Gen
    initScreen(); // start with init screen
    int**board {new int*[screenX]}; // Pointer to pointer array
    initBoard(board);
    ateApple = true; // Set for first pass
    lastMove = 1; // Set for first pass
    fout << "Draw Screen" << endl;
    drawScreen(board);
    QUIT = false;
    int c = getInput();
    lastMove = c;
    nodelay(stdscr, true);
    while (!QUIT){
        fout << "c is: " << c << endl;
        if (c == KEY_RESIZE){
            fout << "Resize" << endl;
            endwin();
            initScreen();
            initBoard(board);
        }
        else if (c == QUIT_CASE){
            fout << "QUIT" << endl;
            endwin();
            break;
        }
        else{
            doLogic(board, c);
            drawScreen(board);
        }
        c = getInput();
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
                board[i][j] = WALL;
            }
            else board[i][j] = EMPTY;
        }
    }
    // Set snake head in the middle of the screen
    snakeHeadCoord[0] = screenX/2;
    snakeHeadCoord[1] = screenY/2;
    snakeTailCoord[0] = snakeHeadCoord[0];
    snakeTailCoord[1] = snakeHeadCoord[1]+snakeLen-2;
    snakeCoords.push_back(make_tuple(snakeHeadCoord[0], snakeHeadCoord[1], ERR));
    snakeCoords.push_back(make_tuple(snakeHeadCoord[0], snakeHeadCoord[1]-1,ERR));
    snakeCoords.push_back(make_tuple(snakeTailCoord[0], snakeTailCoord[1], ERR));
    fout << "Snake set at " << snakeHeadCoord[0] << "," << snakeHeadCoord[1] << endl;
    int appleX = rand() % (screenX-3) + 1;
    int appleY = rand() % (screenY-3) + 1;
    fout << "set apple at (" << appleX << "," << appleY << ")" << endl;
    board[appleX][appleY] = APPLE;
    fout <<"set apple" << endl;
    fout << "Generate walls" << endl;
    int numWalls = rand() % 30 + 5;
    bool valid;
    for (int i = 0; i < numWalls; i++){
        do{
        int wallCoordX = rand() % (screenX-5) + 1;
        int wallCoordY = rand() % (screenY-5) + 1;
        fout << "set at " << wallCoordX << " " << wallCoordY << endl;
        valid = 
        board[wallCoordX][wallCoordY] != SNAKE||
        board[wallCoordX][wallCoordY] != WALL ||
        board[wallCoordX][wallCoordY] != APPLE;
        if (valid)
            board[wallCoordX][wallCoordY] = WALL;
        }while (!valid);
    }

}
void doLogic(int **board, int move){
    if  (move == ERR || 
        (lastMove == KEY_UP && move == KEY_DOWN)    ||
        (lastMove == KEY_DOWN && move == KEY_UP)    ||
        (lastMove == KEY_LEFT && move == KEY_RIGHT) ||
        (lastMove == KEY_RIGHT && move == KEY_LEFT))
        move = lastMove;
    tuple<int, int, int> snakeHead = snakeCoords.front();
    // Head decides move
    if (move != lastMove){
        fout << "Added turn coord" << endl;
        turnCoords.insert(turnCoords.begin(), make_tuple(lastMove, move, get<0>(snakeHead), get<1>(snakeHead), 0)); 
        // last move for before, next move for after, coords of head for coords of turn, 0 for iterator
    }
    fout << "Turn Coords: " << endl;
    for (int i = 0; i < turnCoords.size(); i++){
        tuple <int, int, int, int, int> tupleI = turnCoords.at(i);
        fout << get<0>(tupleI) << ", " << get<1>(tupleI) << " " << get<2>(tupleI) << " " << get<3>(tupleI) << " " << get<4>(tupleI) << endl;
    }
    switch(move){
            case KEY_UP:
                fout << "Move is KEY_UP" << endl;
                snakeHead = make_tuple(get<0>(snakeHead), get<1>(snakeHead)-1, KEY_UP);
                break;
            case KEY_DOWN:
                fout <<"Move is KEY_DOWN" << endl;
                snakeHead = make_tuple(get<0>(snakeHead), get<1>(snakeHead)+1, KEY_DOWN);
                break;
            case KEY_LEFT:
                fout << "Move is KEY_LEFT" << endl;
                snakeHead = make_tuple(get<0>(snakeHead)-1, get<1>(snakeHead), KEY_LEFT);
                break;
            case KEY_RIGHT:
                fout << "Move is KEY_RIGHT" << endl;
                snakeHead = make_tuple(get<0>(snakeHead)+1, get<1>(snakeHead), KEY_RIGHT);
                break;
            default:
                break;
    }
    snakeCoords.at(0) = snakeHead;
    fout << "Passed snake head check" << endl;
    bool turnCoordsEmpty = turnCoords.empty();
    if (!turnCoordsEmpty){
        for (int i = 1; i < snakeCoords.size(); i++){
            // TODO
            // Does this work if the move is below the turn coord? Test in notebook
            tuple<int,int,int> snakePart = snakeCoords.at(i);// check each element of snake coords starting from begin()
            fout << "Set snake part" << endl;
            // check it at turncoords starting from begin()
            tuple<int,int,int,int, int> firstTurn = turnCoords.at(0);
            fout << "Set turn coord" << endl;
            int iterator = get<4>(firstTurn);
            fout << "Set iterator" << endl;
            // if snake at(i) is less than iterator of turn coord, set snake move (get<2>) to before move
            if (i <= iterator){
                fout << "Snake less than iterator" << endl;
                // If snake part coord = turn coord
                if (get<0>(snakePart) == get<2>(firstTurn) && get<1>(snakePart) == get<2>(snakePart)){
                    fout << "Snake part coords == turn coords" << endl;
                    snakePart = make_tuple(get<0>(snakePart),get<1>(snakePart),get<0>(firstTurn));
                    iterator++;
                    }
            }
            // Else set snake move to get<2>
            else
                snakePart = make_tuple(get<0>(snakePart),get<1>(snakePart),get<1>(firstTurn));
            // Set snake at(i) to snakePart
            snakeCoords.at(i) = snakePart;
            fout << "Set snake to coords" << endl;
            // then check iterator
            if (iterator == snakeCoords.size()){
                fout << "Iterator = " << iterator << " erase hit" << endl;
                turnCoords.erase(turnCoords.begin());
            }
            // if iterator is == to size of snake, delete iterator
            // Potentially check eat apple first to add element, requires testing
        }
    }
    fout << "Do move loop reached" << endl;
    for (int i = 1; i < snakeCoords.size(); i++){
        int moveInLoop;
        tuple<int, int, int> snakePart = snakeCoords.at(i);
        if (turnCoordsEmpty)
            moveInLoop = move;
        else
            moveInLoop = get<2>(snakePart);
        switch(moveInLoop){
            case KEY_UP:
                fout << "Move is KEY_UP" << endl;
                snakeCoords.at(i) = make_tuple(get<0>(snakePart), get<1>(snakePart)-1, get<2>(snakePart));
                break;
            case KEY_DOWN:
                fout << "Move is KEY_DOWN" << endl;
                snakeCoords.at(i) = make_tuple(get<0>(snakePart), get<1>(snakePart)+1, get<2>(snakePart));
                break;
            case KEY_LEFT:
                fout << "Move is KEY_LEFT" << endl;
                snakeCoords.at(i) = make_tuple(get<0>(snakePart)-1, get<1>(snakePart), get<2>(snakePart));
                break;
            case KEY_RIGHT:
                fout << "Move is KEY_RIGHT" << endl;
                snakeCoords.at(i) = make_tuple(get<0>(snakePart)+1, get<1>(snakePart), get<2>(snakePart));
                break;
            default:
                break;
        }
    }
    lastMove = move;
}
/* Deprecated
void doLogic(int **board, int move){
    fout << "Do Logic" << endl;
    fout <<"move is " << move << " last turn is " << lastMove << endl;
    fout <<"snake head coord is " << snakeHeadCoord[0] << "," << snakeHeadCoord[1] << endl;  
    if (lastMove != move && move != ERR){
        fout << "add move to turn coords, (" << snakeHeadCoord[0] << "," << snakeHeadCoord[1] << "," << move << ")" << endl; 
        turnCoords.push_back(make_tuple(snakeHeadCoord[0], snakeHeadCoord[1], move));
        fout << "move added" << endl;
    }
    //Head
    fout << "test" << endl;
    tuple<int,int,int> tcback; 
    fout << "test" << endl;
    if (move == ERR || 
        (lastMove == KEY_UP && move == KEY_DOWN)    ||
        (lastMove == KEY_DOWN && move == KEY_UP)    ||
        (lastMove == KEY_LEFT && move == KEY_RIGHT) ||
        (lastMove == KEY_RIGHT && move == KEY_LEFT)
       ) move = lastMove;
    if (!turnCoords.empty() && move != lastMove){
        tcback = turnCoords.back();
        move = get<2>(tcback);
    }
    switch(move){
        case KEY_UP:
            snakeHeadCoord[1] -= 1;
            fout << "test" << endl;
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
        default:
            break;
    }
    lastMove = move;
    //Tail
    int tailMove = move;
    tuple<int, int, int> tcfront;
    if (snakeHitTurn){
        tcfront = turnCoords.front();
        tailMove = get<2>(tcfront);
        snakeHitTurn = false;
        turnCoords.erase(turnCoords.begin());
    }
    fout << "passed head loop" << endl;
    fout << "KEY: " << endl;
    fout << "KEYUP-"<<KEY_UP << endl;
    fout << "KEYDOWN-" << KEY_DOWN << endl;
    fout << "KEY_LEFT" << KEY_LEFT << endl;
    fout << "KEY_RIGHT" << KEY_RIGHT << endl;
    fout << "Tail at (" << snakeTailCoord[0] << "," << snakeTailCoord[1] << ")" << endl;
    fout << "Move is: " << tailMove << endl;
    fout <<  "Head moving to" << snakeHeadCoord[0] << snakeHeadCoord[1] << endl;
    switch(tailMove){
        case KEY_UP:
            snakeTailCoord[1] -= 1;
            fout << "set snake tail" << endl;
            board[snakeTailCoord[0]][snakeTailCoord[1]+1] = EMPTY;
            break;
        case KEY_DOWN:
            snakeTailCoord[1] += 1;
            board[snakeTailCoord[0]][snakeTailCoord[1]-1] = EMPTY;
            break;
        case KEY_LEFT:
            snakeTailCoord[0] -= 1;
            board[snakeTailCoord[0]+1][snakeTailCoord[1]] = EMPTY;
            break;
        case KEY_RIGHT:
            snakeTailCoord[0] += 1;
            board[snakeTailCoord[0]-1][snakeTailCoord[1]] = EMPTY;
            break;
    }
    fout << "Tail moving to (" << snakeTailCoord[0] << "," << snakeTailCoord[1] << ")" << endl;
    board[snakeTailCoord[0]][snakeTailCoord[1]] = SNAKE;
    snakeHitTurn = snakeTailCoord[0] == get<0>(tcfront) && snakeTailCoord[1] == get<1>(tcfront);
    fout << "check if hit obstacle" << endl;
    if (board[snakeHeadCoord[0]][snakeHeadCoord[1]] == WALL || board[snakeHeadCoord[0]][snakeHeadCoord[1]] == SNAKE){ // If hit obstacle
        fout << "hit obstacle at " << snakeHeadCoord[0] << "," << snakeHeadCoord[1] << endl;
        fout << "last turn " << lastMove << " current move" << move << endl;
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
        switch(tailMove){
            case KEY_UP:
            snakeTailCoord[1] -= 1;
            board[snakeTailCoord[0]][snakeTailCoord[1]+1] = SNAKE;
            break;
        case KEY_DOWN:
            snakeTailCoord[1] += 1;
            board[snakeTailCoord[0]][snakeTailCoord[1]-1] = SNAKE;
            break;
        case KEY_LEFT:
            snakeTailCoord[0] -= 1;
            board[snakeTailCoord[0]+1][snakeTailCoord[1]] = SNAKE;
            break;
        case KEY_RIGHT:
            snakeTailCoord[0] += 1;
            board[snakeTailCoord[0]-1][snakeTailCoord[1]] = SNAKE;
            break;
        }
    }
    fout << "set head to snake" << endl;
    board[snakeHeadCoord[0]][snakeHeadCoord[1]] = SNAKE;
}*/
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
            else
                printw("%d", (board[x][y]));
            refresh();
        }
    }
    attron(COLOR_PAIR(SNAKE));
    for (int i = 0; i < snakeCoords.size(); i++){
        tuple<int, int, int> snakePart = snakeCoords.at(i);
        move(get<1>(snakePart), get<0>(snakePart));
        printw("0");
    }
    refresh();
    attroff(COLOR_PAIR(SNAKE));
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




