//DANIEL VOLCHEK-NCURSES_GAMES_SNAKE
#include "includes.h"
using namespace std;
namespace snake{
//Err checking
ofstream fout;
//snake length
int snakeLen = 3;
//Screen Size
int screenY;
int screenX;
//Turn Vector and last turned
vector<tuple<int,int,int, int>> snakeCoords; // Current Coords X, Y Last Coords X, Y
int lastMove; // Defined with KEY_UP KEY_DOWN etc...
int score = 0;
//QUIT bool
bool QUIT;
//Apple eaten bool
bool ateApple;
bool snakeHitTurn;
void runGame(){
    fout.open("snake_errfile");
    //getErrFile();
    srand(time(NULL)); // Rand Gen
    initScreen(); // start with init screen
    int**board {new int*[screenX]}; // Pointer to pointer array
    initBoard(board);
    ateApple = true; // Set for first pass
    QUIT = false;
    fout << "Draw Screen" << endl;
    drawScreen(board);
    int c;
    c = getInput();
    while (c != KEY_UP && c != KEY_LEFT && c != KEY_RIGHT)
        c = getInput();
    lastMove = c;
    nodelay(stdscr, true);
    while (!QUIT){
        if (c == KEY_RESIZE){
            fout << "Resize" << endl;
            endwin();
            initScreen();
            initBoard(board);
        }
        else if (c == QUIT_CASE){
            fout << "QUIT" << endl;
            break;
        }
        else if (c == KEY_ESC){
            while(true){
                c = getInput();
                if (c == KEY_ESC)
                    break;
                if (c == QUIT_CASE){
                    QUIT = true;
                    break;
                }
            }
        }
        else{
            doLogic(board, c);
            drawScreen(board);
            }
        c = getInput();
    }
    endwin();
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
    curs_set(0); // Remove cursor
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
    init_pair(SNAKE, COLOR_RED, COLOR_WHITE);
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
    if (snakeCoords.empty()){
        int snakeHeadCoordX = screenX/2;
        int snakeHeadCoordY = screenY/2;
        snakeCoords.push_back(make_tuple(snakeHeadCoordX, snakeHeadCoordY, snakeHeadCoordX, snakeHeadCoordY));
        board[snakeHeadCoordX][snakeHeadCoordY] = SNAKE;
        snakeCoords.push_back(make_tuple(snakeHeadCoordX, snakeHeadCoordY+1, snakeHeadCoordX, snakeHeadCoordY+1));
        board[snakeHeadCoordX][snakeHeadCoordY+1] = SNAKE;
        snakeCoords.push_back(make_tuple(snakeHeadCoordX, snakeHeadCoordY+2, snakeHeadCoordX, snakeHeadCoordY+2));
        board[snakeHeadCoordX][snakeHeadCoordY+2] = SNAKE; 
        snakeCoords.push_back(make_tuple(snakeHeadCoordX, snakeHeadCoordY+3, snakeHeadCoordX, snakeHeadCoordY+3));
        //board[snakeHeadCoordX][snakeHeadCoordY+3] = SNAKE;         
    }
    for (int i = 0; i < 5; i++){
        int appleX = rand() % (screenX-3) + 1;
        int appleY = rand() % (screenY-3) + 1;
        board[appleX][appleY] = APPLE;
    }
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
    //TODO For loop through elements of snake head
    //TODO move snake head
    //TODO then move every element to position of last element
    //TODO Snake head moves, then element behind it moves to where snake head was, then element behind...
    // If move is the same as last move 
    // Or move is the opposite of last move
    // set move to last move
    if  (move == ERR || 
        (lastMove == KEY_UP && move == KEY_DOWN)    ||
        (lastMove == KEY_DOWN && move == KEY_UP)    ||
        (lastMove == KEY_LEFT && move == KEY_RIGHT) ||
        (lastMove == KEY_RIGHT && move == KEY_LEFT))
        move = lastMove;
    tuple<int, int, int, int> snakeHead = snakeCoords.front();
    // Head decides move
    switch(move){
            case KEY_UP:
                fout << "Head move is KEY_UP" << endl;
                snakeHead = make_tuple(get<0>(snakeHead), get<1>(snakeHead)-1, get<0>(snakeHead), get<1>(snakeHead));
                break;
            case KEY_DOWN:
                fout <<"Head move is KEY_DOWN" << endl;
                snakeHead = make_tuple(get<0>(snakeHead), get<1>(snakeHead)+1, get<0>(snakeHead), get<1>(snakeHead));
                break;
            case KEY_LEFT:
                fout << "Head move is KEY_LEFT" << endl;
                snakeHead = make_tuple(get<0>(snakeHead)-1, get<1>(snakeHead), get<0>(snakeHead), get<1>(snakeHead));
                break;
            case KEY_RIGHT:
                fout << "Head move is KEY_RIGHT" << endl;
                snakeHead = make_tuple(get<0>(snakeHead)+1, get<1>(snakeHead), get<0>(snakeHead), get<1>(snakeHead));
                break;
            default:
                break;
    }
    snakeCoords.at(0) = snakeHead;
    fout << "Passed snake head check" << endl;
    for (int i = 1; i < snakeCoords.size(); i++){
        tuple<int, int, int, int> currentSnakeHead = snakeCoords.at(i);
        tuple<int, int, int, int> lastSnakeHead = snakeCoords.at(i-1);
        int newX = get<2>(lastSnakeHead);
        int newY = get<3>(lastSnakeHead);
        // Set snake coord at i to x and y of snake part above itself
        // Set last coords to its own previous coords
        snakeCoords.at(i) = make_tuple(newX, newY, get<0>(currentSnakeHead), get<1>(currentSnakeHead));
        board[newX][newY] = SNAKE;
   }
    tuple<int, int, int, int> snakeBack = snakeCoords.back();
    board[get<2>(snakeBack)][get<3>(snakeBack)] = EMPTY;
    // TODO draw empty spot at end snake part
    int occupiedSpot = board[get<0>(snakeHead)][get<1>(snakeHead)];
    if (occupiedSpot == WALL || occupiedSpot == SNAKE){
        QUIT = true;
    }
    int snakeX = get<0>(snakeHead);
    int snakeY = get<1>(snakeHead);
    if (board[snakeX][snakeY] == APPLE){
        // Increment score
        // TODO add high score
        score++; 
        board[snakeX][snakeY] = EMPTY;
        tuple<int, int, int, int> endSnake = snakeCoords.back();
        // Set location for new snake part
        switch (lastMove){
            case KEY_UP: 
            endSnake = make_tuple(get<0>(endSnake), get<1>(endSnake)+1, get<0>(endSnake), get<1>(endSnake));
            break;
            case KEY_DOWN: 
            endSnake = make_tuple(get<0>(endSnake), get<1>(endSnake)-1, get<0>(endSnake), get<1>(endSnake));
            break;
            case KEY_LEFT:
            endSnake = make_tuple(get<0>(endSnake)+1, get<1>(endSnake), get<0>(endSnake), get<1>(endSnake));
            break;
            case KEY_RIGHT: 
            endSnake = make_tuple(get<0>(endSnake)-1, get<1>(endSnake), get<0>(endSnake), get<1>(endSnake));
            break;
            default:
            break;
        }
        snakeCoords.push_back(endSnake);
        bool valid;
        do{
            // Set new random move 
            int appleX = rand() % (screenX-3) + 1;
            int appleY = rand() % (screenY-3) + 1;
            // Check random location not on wall
            valid = board[appleX][appleY] != WALL;
            if (valid){
                board[appleX][appleY] = APPLE;
            }
        }
        while(!valid);
        
    }
    lastMove = move;
}
void drawScreen(int** board){
    //TODO refactor to draw board once then only draw snake and new apples
    for (int x = 0; x < screenX; x++){
        for (int y = 0; y < screenY; y++){
            move(y, x);
            if (board[x][y] == WALL){
                attron(COLOR_PAIR(WALL));
                printw("x");
                attroff(COLOR_PAIR(WALL));
            }
            else if (board[x][y] == SNAKE){
                attron(COLOR_PAIR(SNAKE));
                printw("0");
                attroff(COLOR_PAIR(SNAKE));
            }
            else if (board[x][y] == APPLE){
                attron(COLOR_PAIR(APPLE));
                printw("0");
                attroff(COLOR_PAIR(APPLE));
            }
            else{
                printw(" "); // potentially switch to drawing blank space at the back of snake
                }
                //printw("%d", (board[x][y]));
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
}



