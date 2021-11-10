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
vector<vector<tuple<int, int>>> memVect; // Vector(memory) of vector(boards) of tuples(live cell coords)
//Screen Size
int screenY;
int screenX;

//QUIT bool
bool START = false;
bool QUIT = false;
//function decleration
void initScreen(); // Init Screen
void initBoard(int** board); // Init board
void doLogic(int** board); // Do logic
void drawScreen(int** board, bool setting); // Draw screen
bool checkLiveState(int** board, int x, int y); // check state of element on x y
void setState(int** board); // Change board with user input
void runGame(int **board); // Deprecated for now
void getErrFile(); // Err file for debugging
//commands
void enterCommand(int **board);
void help(int **board);
void skip(string flag, int **board);
void setMem(string flag);
void start();
void stop();
void clearBoard(int **board);
void mod(int **board);
void step(string flag, int **board);
void quit();
void save(string filename, int **board);
void load(string filename, int **board);
void setSpeed(string flag, int **board);

int main(){
    getErrFile();
    initScreen(); // start with init screen
    int**board {new int*[screenX]}; // Pointer to pointer array
    fout << "Init Board" << endl;
    initBoard(board);
    fout << "Draw Screen" << endl;
    drawScreen(board, false);
    runGame(board); 
    endwin();
    return 0;
}
void runGame(int **board){
   int c;
   help(board);
   while(!QUIT){
        c = getch();
        if (c == '/'){
            enterCommand(board);
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
                enterCommand(board);
                c = ' ';
            }
            else{
                doLogic(board);
                drawScreen(board, false);
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
    nodelay(stdscr, true);
    keypad(stdscr, true); // Enables keypad input
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

void enterCommand(int **board){
    echo();
    curs_set(1);
    move(screenY, 0);
    nodelay(stdscr, false);
    printw("/");
    move(screenY, 1);
    string command;
    int ch;
    while (1){
        ch = getch();
        fout << ch << endl;
        if (ch == ENTER_KEY){
            break;
        }
        else if (ch == 263){ // backspace
            command = command.substr(0, command.length()-1);
            mvprintw(screenY, command.length()+1, " ");
            move(screenY, command.length());
        }
        else
            command += ch;
    }
    clear();
    string action;
    string flag;
    for (int i = 0; i < command.length(); i++){
        if (command.at(i) == ' '){
            action = command.substr(0, i);
            flag = command.substr(i, command.length() - i);
        }
    }
    if (flag == "")
        action = command;
    fout << "Command is: " << command << " flag is " << flag << endl;
        if(action=="help") help(board);
        else if(action=="skip") skip(flag, board);
        else if(action=="setmem") setMem(flag);
        else if(action=="start") start();
        else if(action=="stop") stop();
        else if(action=="clear") clearBoard(board);
        else if(action=="mod") mod(board);
        else if(action=="step") step(flag, board);
        else if(action=="quit") quit();
        else if(action=="save") save(flag, board);
        else if(action=="load") load(flag, board);
        else if(action=="speed") setSpeed(flag, board);
        else help(board);
    noecho();
    curs_set(0);
    nodelay(stdscr, true);
//wait for enter press
//help - Goes through all commands with options
    // clearBoard screen output each command line by line
//skip x - Skips X increments 
//setmem - set number of states to remember
//keep 5-10 boards in memory and skip/step through them backwards
//start - Runs program
//stop - pauses program
//clearBoard - clearBoards board
//mod - change input to GoL
//step - step once before pausing
//step x - step through x times showing change
//q or quit - exit
//save filename - save state to file
//load filename - load state from file
//speed - change speed in ms
}
void help(int **board){
    clear();
    fout << "help" << endl; 
    mvprintw(0, 0, "help: outputs help for commands"); 
    mvprintw(1, 0, "skip n: skips n times");
    mvprintw(2, 0, "setmem n: sets memory range");
    mvprintw(3, 0, "start: starts program running");
    mvprintw(4, 0, "stop: stops program running");
    mvprintw(5, 0, "clear: clears state");
    mvprintw(6, 0, "mod: enters modification function");
    mvprintw(7, 0, "step n: steps through n times");
    mvprintw(8, 0, "quit: exits program");
    mvprintw(9, 0, "save filename: saves state to file");
    mvprintw(10, 0, "load filename: loads state from file");
    mvprintw(11, 0, "speed n: sets speed in ms");
    mvprintw(12, 0, "enter q to exit");
    char c;
    noecho();
    while (c != 'q'){
        c = getch();
    }
    clear();
    drawScreen(board, false);
}
void skip(string flag, int **board){
    fout << "skip" << endl;
    int n = stoi(flag);
    if (n >= 0){
        for (int i = 0; i < n; i++){
            doLogic(board);
        }
    }
    START = false;
    // add n is negative with memory
}
void setMem(string flag){
    fout << "setMem" << endl;
    int n = stoi(flag);
    memory = n;
}
void start(){
    fout << "start" << endl;
    START = true;
}
void stop(){
    fout << "stop" << endl;
    START = false;
}
void clearBoard(int **board){
    fout << "clear board" << endl;
    for (int i = 0; i < screenX; i++){
        for (int j = 0; j < screenY; j++){
            board[i][j] = 0;
        }
    }
}
void mod(int **board){
    fout << "mod" << endl;
    setState(board);
}
void step(string flag, int **board){
    fout << "step" << endl;
    int n = stoi(flag);
    if (n >= 0){
        for (int i = 0; i < n; i++){
            doLogic(board);
            drawScreen(board, false);
        }
    }
    START = false;
}
void quit(){
    fout << "quit" << endl;
    QUIT = true;
}
void save(string filename, int **board){
    fout << "save" << endl;
}
void load(string filename, int **board){
    fout << "load" << endl;
}
void setSpeed(string flag, int **board){
    fout << "setSpeed" << endl;
    int n = stoi(flag);
    if (n >=0)
        sleepTime = n;
    else
        help(board);
}

