//File name:/home/danielvolchek/ncursesgames/pong/pong.cpp
//Daniel Volchek
//Section_01

//Code:
#include <iostream>
#include <ncurses.h>
#include <tuple>
#include <fstream>

#define QUIT_CASE -10
int **board;
tuple <int, int> paddleOneCoord;
tuple <int, int> paddleTwoCoord;
int paddleLength;
int paddleWidth;
tuple <int, int> ballCoord;
int trajectory;
int score1;
int score2;

void runGame();
void initErrFile();
void initScreen();
void resizeScreen();
void getInput();
void moveBall();


using namespace std;

int main(){
    initErrFile();
    runGame();
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
    curs_set(0); // Remove cursor
    noecho();
    cbreak();
    nodelay(stdscr, true);
    keypad(stdscr, true); // Enables keypad input
    start_color();
    refresh();
    getmaxyx(stdscr, screenY, screenX); // Assigns screen size variables
    fout << "Screen X: " << screenX << " Screen Y: " << screenY << endl;
 
}
void runGame(){
    initScreen();
    initPaddles();
    drawPaddles();
    while (RUNNING){
        int c = getInput();
        if (c == QUIT_CASE){
            break;
        }
    }
    endwin();
}
void initErrFile(){
    // Open File to read from
    ifstream errFileIn;
    errFileIn.open("errfiles/filecount", ios::out); // Get file ending from filecount
    if (errFileIn.is_open()){
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
    // If no directory for files
    else{
        fout.open("errfile");
    }
}
void initPaddles(){
    // Paddles should be one fifth of the vertical length
    paddleLength = screenY / 5;
    paddleWidth = screenX/25;
    // Tuple is x, y
    paddleOneCoord = make_tuple(0, screenY/2);
    paddleTwoCoord = make_tuple(screenX-1, screenY/2);
}
void movePaddles(int direction){
    paddleYMove = get<1>(paddleOneCoord) + direction;
    if (paddleYMove > screenY-1 || paddleYMove < 0)
        return;
    paddleOneCoord = make_tuple(0, paddleYMove);
}
int getInput(){
    int c = getch();
    switch c:
        case KEY_LEFT: return -1;
        case KEY_RIGHT: return 1;
        case 'q': return QUIT_CASE;
        default: return 0;
}
void drawPaddles(){
    for (int i = 0; i < paddleWidth; i++){
        mvvline(get<1>(paddleOneCoord), i, ACS_HLINE, paddleLength);
        //mvvline(get<1>(paddleTwoCoord), get<0>(paddleTwoCoord) - i, ACS_HLINE, paddleLength);
    }
}
