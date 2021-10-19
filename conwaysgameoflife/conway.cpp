//DANIEL VOLCHEK-NCURSES_GAMES_CONWAY_LIFE
//Includes
#include <iostream>
#include <ncurses.h> // Graphics library
#include <fstream> //Err checking
#include <string> // File Checking
#include <vector> // Coords
#include <tuple> // Coords
#include <thread> // Slow down program
#include <chrono> // Slow down program

using namespace std;

//Defines
#define DEAD 0
#define LIVE  1
#define ENTER_KEY 10
#define KEY_ESC 27

//Err checking
ofstream fout;

//Sleep time
int sleepTime = 250; // Default

int memory = 0; // Default
Vector<Vector<tuple<int, int>>> memVect; // Vector(memory) of vector(boards) of tuples(live cell coords)
//Screen Size
int screenY;
int screenX;

//QUIT bool
bool START = false;
bool QUIT = false;
//function decleration
void initScreen(); // Init Screen
string enterCommand(); // Enter command output command
void initBoard(int** board); // Init board
void doLogic(int** board); // Do logic
void drawScreen(int** board); // Draw screen
bool checkLiveState(int** board, int x, int y); // check state of element on x y
void setState(int** board); // Change board with user input
void runGame(); // Deprecated for now
void getErrFile(); // Err file for debugging
//commands
string enterCommand();
bool help(string command);
bool skip(int n, int **board);
bool setMem(int n);
bool start();
bool stop();
bool clear();
bool mod(int **board);
bool step(int n, int **board);
bool quit();
bool save(string filename, int **board);
bool load(string filename, int **board);
bool setSpeed(int n);

int main(){
    getErrFile();
    initScreen(); // start with init screen
    int**board {new int*[screenX]}; // Pointer to pointer array
    fout << "Init Board" << endl;
    initBoard(board);
    fout << "Draw Screen" << endl;
    drawScreen(board, false);
    runGame(int **board); 
    endwin();
    return 0;
}
void runGame(int **board){
   int c;
   while(!QUIT){
        c = getch();
        if (c == '/'){
            enterCommand();
        }
        while (START){
            if (c == KEY_RESIZE){
                fout << "Resize" << endl;
                endwin();
                initScreen();
                initBoard(board);
            }
            else if (QUIT){
                fout << "QUIT" << endl;
                break;
            }
            else if (c == '/'){
                enterCommand();
            }
            else{
                doLogic(board);
                drawScreen(board);
                }
            c = getch();
        }
    }

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
    nodelay(stdscr, true);
    start_color();
    refresh();
    getmaxyx(stdscr, screenY, screenX); // Assigns screen size variables
    fout << "Screen X: " << screenX << " Screen Y: " << screenY << endl;
    screenY--; // Leave room for commands
    init_pair(LIVE, COLOR_BLUE, COLOR_BLACK);
}
void initBoard(int** board){
    for (int i = 0; i < screenX; i++){
        board[i] = new int[screenY];
    }
    for (int i = 0; i < screenX; i++){
        for (int j = 0; j < screenY; j++){
            fout << "Set board at " << i << "," << j << endl;
            board[i][j] = DEAD;
        }
    }
}
void setState(int** board){
    fout << "Setting Initial State" << endl;
    drawScreen(board, true);
    curs_set(1);
    int x = 0;
    int y = 0;
    while(1){
       int c = getch();
       fout << "c: " << c << endl;
       if (c == KEY_UP){
            if (y-1 >= 0 && y-1 <= screenY-1){
                y--;
            }
       }
       if (c == KEY_DOWN){
            if (y + 1 >= 0 && y +1 <= screenY-1){
                y++;
            }
       }
       if (c == KEY_LEFT){
            if (x - 1 >= 0 && x -1 <= screenX -1){
                x--;
            }
       }
       if (c == KEY_RIGHT){
            if (x + 1 >= 0 && x + 1 <= screenX-1){
                x++;
            }
       }
       fout << "attempting move to: " << x << "," << y << endl;
       move(y, x);
       if (c == ENTER_KEY){
            fout << "Changing " << x << ", " << y << " from " << board[x][y] << " to " << !(board[x][y]) << endl;
            board[x][y] = !(board[x][y]);
            move(y, x);
            if (board[x][y]){
                attron(COLOR_PAIR(LIVE));
                printw("%d", board[x][y]);
                attroff(COLOR_PAIR(LIVE));
            }
            else{
                printw("%d", board[x][y]);
            }
       }
       if (c == '/'){
            fout << "Found break" << endl;
            break;
       }
    }
        enterCommand(board);
}
void doLogic(int **board){
    fout << "Do logic" << endl;
    vector <tuple<int, int>> liveCoords;
    vector <tuple<int, int>> deadCoords;
    for (int i = 0; i < screenX; i++){
        for (int j = 0; j < screenY; j++){
            if (checkLiveState(board, i, j)){
                liveCoords.push_back(make_tuple(i, j));
            }
            else{
                // If not live check if cell was live and switch
                if (board[i][j])
                    deadCoords.push_back(make_tuple(i, j));
            }
        }
    }
    // Sets boards
    for (int i = 0; i < liveCoords.size(); i++){
        tuple<int, int> coords = liveCoords.at(i);
        board[get<0>(coords)][get<1>(coords)] = LIVE;
    }
    for (int i = 0; i < deadCoords.size(); i++){
        tuple<int, int> coords = deadCoords.at(i);
        board[get<0>(coords)][get<1>(coords)] = DEAD;
    }
    // Sleeps thread
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
}
void drawScreen(int** board, bool setting){
    for (int x = 0; x < screenX; x++){
        for (int y = 0; y < screenY; y++){
            move(y, x);
            if (board[x][y]){
                attron(COLOR_PAIR(LIVE));
                printw("%d", board[x][y]);
                attroff(COLOR_PAIR(LIVE));
            }
            else{
                if (setting)
                    printw("0");
                else
                    printw(" ");
            }
        }
    }
}

bool checkLiveState(int** board, int x, int y){
    /*
       0 0 0 0
       0 0 0 0
       0 0 0 0
       0 0 0 0
                */
    // Check neighbors
    // If x - 1 < 0 or = to screen or y - 1 < 0 or = to screen
    // Don't check
    int neighbors = 0;
    int cellState; 
    
    cellState = board[x][y];
    if (cellState)
        fout << "Found Live" << endl;
    // loop through array to check each x + element in board
    int check[8][2] = { 
    {-1, -1}, {-1,0}, {-1, 1},
    {0, -1},  {0, 1},
    {1, -1}, {1, 0}, {1, 1}
    };
    for (int i = 0 ; i < 8; i++){
        int checkAt[2] = {check[i][0], check[i][1]};
        int checkX = checkAt[0];
        int checkY = checkAt[1];
        // If out of boundaries
        if (x + checkX < 0 || x + checkX >= screenX){
            continue;
        }
        if (y + checkY < 0 || y + checkY >= screenY){
            continue;
        }
        // If cell neighbor is live
        if (board[x+checkX][y+checkY]){
            neighbors++;
        }
    }
    // If live
    if (cellState){
        fout << "Neighbor count: " << neighbors << endl;
        return neighbors == 2 || neighbors == 3;
    }
    // If dead
    return neighbors == 3;
}
void getErrFile(){
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
    else{
        fout.open("errfile");
    }
}

string enterCommand(int **board){
    echo();
    curs_set(1);
    move(screenY+1, 0);
    string command;
    int ch;
    while (ch != KEY_ENTER){
        ch = getch(); 
    }
    string action;
    string flag;
    int n;
    for (int i = 0; i < command.length(); i++){
        if (command.at(i) == ' '){
            action = command.substr(0, i);
            flag = command.substr(i, command.length() - i);
        }
    }
    try{
        n = stoi(s);
    }
    catch(...){
        n = -1;
    }
    fout << "Command is: " << command << " flag is " << flag << endl;
    switch(command){
        case "help": help(); break;
        case "skip": skip(n) break;
        case "setmem": setMem(n); break;
        case "start": start(); break;
        case "stop": stop(); break;
        case "clear": clear(); break;
        case "mod": mod(); break;
        case "step": step(n); break;
        case "quit": quit(); break;
        case "save": save(string flag); break;
        case "load": load(string flag); break;
        case "speed": setSpeed(n); break;
        default: help(); break;
    }
    noecho();
    curs_set(0);
        

//wait for enter press
//help - Goes through all commands with options
    // clear screen output each command line by line
//skip x - Skips X increments 
//setmem - set number of states to remember
//keep 5-10 boards in memory and skip/step through them backwards
//start - Runs program
//stop - pauses program
//clear - clears board
//mod - change input to GoL
//step - step once before pausing
//step x - step through x times showing change
//q or quit - exit
//save filename - save state to file
//load filename - load state from file
//speed - change speed in ms
return NULL;
}
bool help(string command){
    
}
bool skip(int n, int **board){
    if (n >= 0){
        for (int i = 0; i < n; i++){
            doLogic(board);
        }
    }
    // add n is negative with memory
}
bool setMem(int n){
    memory = n;
}
bool start(){
    START = true;
}
bool stop(int **board){
    START = false;
}
bool clear(int **board){
}
bool mod(int **board){
    setState(board);
    return true;
}
bool step(int n, int **board){
    if (n >= 0){
        for (int i = 0; i < n; i++){
            doLogic(board);
            drawScreen(board, false);
        }
    }
}
bool quit(){
    QUIT = true;
}
bool save(string filename, int **board){

}
bool load(string filename, int **board){

}
bool setSpeed(int n){
    if (n >=0)
        sleepTime = n;
    else
        help();
}

