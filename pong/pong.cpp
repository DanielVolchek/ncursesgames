//File name:/home/danielvolchek/ncursesgames/pong/pong.cpp
//Daniel Volchek
//Section_01

//Code:
#include "includes.h"
using namespace std;
namespace pong{
ofstream fout;
int screenY;
int screenX;
paddle paddleOne;
paddle paddleTwo;
ball ballOne;
bool scoreChanged;

void initScreen(){
    fout << "Init Screen" << endl;
    if (stdscr != NULL){ // If called on resize
        fout << "Resize called" << endl;
        erase();
        endwin();
    }
    // standard functions
    initscr();
    start_color();
    curs_set(0); // Remove cursor
    noecho();
    cbreak();
    keypad(stdscr, true); // Enables keypad input
    nodelay(stdscr, true);
    start_color();
    refresh();
    getmaxyx(stdscr, screenY, screenX); // Assigns screen size variables
    fout << "Screen X: " << screenX << " Screen Y: " << screenY << endl;
    init_pair(PLAYER_ONE, COLOR_GREEN, COLOR_BLACK);
    init_pair(PLAYER_TWO, COLOR_GREEN, COLOR_BLACK);
}
void resizeScreen(){
    getmaxyx(stdscr, screenY, screenX);
    clear();
    initPaddles();
    initBall();
}
void runGame(){
    fout.open("pong_errfile");
    scoreChanged = false;
    int lastMove;
    initScreen();
    initPaddles();
    initBall();
    drawScreen();
    int c;
    while (1){
        if (paddleOne.score == 10){
            endGame(true);
            break;
        }
        else if (paddleTwo.score == 10){
            endGame(false);
            break;
        }
        c = getInput();
        if (c == QUIT_CASE){
            break;
        }
        if (c == KEY_ESC){
            while(true){
                c = getInput();
                if (c == KEY_ESC){
                    break;
                }
                if (c == QUIT_CASE){
                    goto stop;
                }
            }
        }
        if (c == KEY_RESIZE){
            initScreen();
            initPaddles();
            initBall();
        }
        if (c == 1 || c == -1){
            movePaddles(&paddleOne, c, &lastMove);
        }
        doCPUMove();
        incrementBall();
        drawScreen();
    }
    stop:
    endwin();
    flushinp();
}
void endGame(bool win){
    if (win)
        cout << "You win!" << endl;
    else
        cout << "You lose!" << endl;
}
void initPaddles(){
    // Paddles should be one fifth of the vertical length
    paddleOne.length = screenY / 5;
    paddleTwo.length = screenY / 5;
    //Player speeds
    paddleOne.velocity = 1;
    paddleOne.max_velocity = 3;
    //Cpu speeds
    paddleTwo.velocity = 1;
    paddleTwo.max_velocity = 1;
    //Initial paddle positions
    paddleOne.setCoord(0, screenY/2-(paddleOne.length/2));
    paddleTwo.setCoord(screenX-1, screenY/2-(paddleOne.length/2));
}
void initBall(){
    //Initial location
    ballOne.x = screenX/2;
    ballOne.y = screenY/2;
    //Initial speed
    //TODO set random starting direction
    if (ballOne.lastHitBy != PLAYER_TWO){
        ballOne.vx = 1;
        ballOne.vy = -1;
        ballOne.lastHitBy = PLAYER_ONE;
    }
    else{
        if (ballOne.lastHitBy == PLAYER_ONE){
            ballOne.vx = 1;
        }
        else{
            ballOne.vx = -1;
        }
        ballOne.vy = 1;
    }
    //TODO then set starting direction to change based on last score
}
void movePaddles(paddle* p, int direction, int *lastMove){
    flushinp();
    // If move is the same as last move increase velocity of paddle
    if (direction == *lastMove){
        p -> velocity++;
        if (p -> velocity > p-> max_velocity)
            p -> velocity = p -> max_velocity;
    }
    // Otherwise decrease velocity of paddle
    else{
        *lastMove = direction;
        p -> velocity--;
        if (p -> velocity <= 0)
            p -> velocity = 1;
    }
    int paddleYMove = p -> y + (direction*p->velocity); 
    clearPaddle(p);
    //If paddle would go through wall set to wall instead
    if (paddleYMove + p -> length > screenY){
        p -> setCoord(p -> x, screenY - p -> length);
        return;
    }
    else if (paddleYMove < 0){
        p -> setCoord(p -> x,0);
        return;
    }
    //Otherwise set to location paddle should be
    p -> setCoord(p->x, paddleYMove);
}
void clearPaddle(paddle *p){
    if (p == &paddleOne){
        for (int i = 0; i < p -> length; i++){
            for (int j = 0; j < p -> width; j++){
                mvprintw(p -> y + i, p -> x + j, " ");
            }
        }
    }
    else{
        for (int i = 0; i < p -> length ; i++){
            for (int j = 0; j < p -> width; j++){
                mvprintw(p -> y + i, p -> x - j, " ");
            }
        }
    }
}
void doCPUMove(){
    //TODO
    int move;
    if (ballOne.vy >= 0){
        move = 1;
    }
    else{
        move = -1;
    }
    int lastMove = -move;
    if (ballOne.x > screenX/2 && ballOne.lastHitBy == PLAYER_ONE)
        movePaddles(&paddleTwo, move, &lastMove);
    else if (ballOne.lastHitBy == PLAYER_TWO && paddleTwo.y != screenY/2-(paddleOne.length/2)){
        paddleTwo.y > screenY/2-(paddleOne.length/2) ? move = -1 : move = 1;
        movePaddles(&paddleTwo, move, &lastMove);
    }
}
void incrementBall(){
    // get future move
    int moveX = ballOne.x + ballOne.vx;
    int moveY = ballOne.y + ballOne.vy;
    // clear original location of ball
    mvprintw(ballOne.y, ballOne.x, " "); 
    // if ball hit player wall increment correct score and reset ball 
    if (moveX <= 0){
       scoreChanged = true;
       paddleTwo.score++;
       initBall();
    }
    else if (moveX >= screenX-1){
        paddleOne.score++;
        scoreChanged = true;
        initBall();
    }
    else{
        ballOne.x = moveX;
    }
    // if ball hit side wall reverse direction of travel
    if (moveY <= 0){
        ballOne.y = 0;
        ballOne.vy = -ballOne.vy;
    } 
    else if (moveY >= screenY){
        ballOne.y = screenY-1;
        ballOne.vy = -ballOne.vy;
    }
    else{
        ballOne.y = moveY;
    }
     if (checkBallHit()){
        paddle *p;
        if (ballOne.x > screenX/2){
            p = &paddleTwo;
        }
        else{
            p = &paddleOne;
        }
        double hitPercent = 1.0 * (ballOne.y - p -> y) / p -> length;
        fout << "ball one y: " << ballOne.y << endl;
        fout << "p -> y: " << p -> y << endl;
        fout << "p -> length: " << p -> length;
        fout << "hit percent:" << hitPercent << endl;
        if (hitPercent < 0.4){
            ballOne.vy = (ballOne.vy*1.25);
        }
        if (hitPercent > 0.6){
            ballOne.vy = (ballOne.vy*1.25);
        }
        else{
            ballOne.vy = 1;
        }
        ballOne.vx = -ballOne.vx;
     }
}
bool checkBallHit(){
    bool ballBetweenX;
    bool ballBetweenY;
    // if ball is on player half
    if (ballOne.x <= screenX/2){
        ballBetweenX = (ballOne.x >= paddleOne.x && ballOne.x <= paddleOne.x + paddleOne.width);
        ballBetweenY = (ballOne.y >= paddleOne.y && ballOne.y <= paddleOne.y + paddleOne.length);
        if (ballBetweenX && ballBetweenY){
            ballOne.lastHitBy = PLAYER_ONE;
        }
    }
    // if ball is on cpu half
    else if (ballOne.x >= screenX/2){
        ballBetweenX = (ballOne.x <= paddleTwo.x && ballOne.x >= paddleTwo.x - paddleOne.width);
        ballBetweenY = (ballOne.y >= paddleTwo.y && ballOne.y <= paddleTwo.y + paddleOne.length);
        if (ballBetweenX && ballBetweenY){
            ballOne.lastHitBy = PLAYER_TWO;
        }
    }
   
    //bool ballHitSide = (ballOne.x >= paddleOne.x && ballOne.x <= paddleOne.width && (ballOne.y == paddleOne.x || ballOne.y == paddleOne.x + paddleOne.length)) ||
    //(ballOne.x >= paddleTwo.x && ballOne.x <= paddleTwo.width && (ballOne.y == paddleTwo.x || ballOne.y == paddleTwo.x + paddleTwo.length)); 
    return (ballBetweenX && ballBetweenY);// || ballHitSide;
}
int getInput(){
    int c = getch();
    switch (c){
        case KEY_UP: return -1;
        case KEY_DOWN: return 1;
        case KEY_ESC: return KEY_ESC;
        case KEY_RESIZE: return KEY_RESIZE;
        case 'q': return QUIT_CASE;
        default: return 0;
    }
}
void drawPaddles(){
    for (int i = 0; i < paddleOne.length; i++){
        for (int j = 0; j < paddleOne.width; j++){
            mvprintw(paddleOne.y + i, paddleOne.x + j, "|");
        }
    }
    for (int i = 0; i < paddleTwo.length; i++){
        for (int j = 0; j < paddleTwo.width; j++){
            mvprintw(paddleTwo.y + i, paddleTwo.x - j, "|");
        }
    }
}
void drawBall(){
   mvprintw(ballOne.y, ballOne.x, "o"); 
}
void drawMid(){
    for (int i = 0; i < screenY; i+=2){
        mvprintw(i, screenX/2, "|");
    }
}
void drawScore(){
    if (paddleOne.score == 10 || paddleTwo.score == 10)
        return;
    int length1;
    int length2;
    string s1 = getLetter(paddleOne.score, &length1);
    string s2 = getLetter(paddleTwo.score, &length2);
    int x1 = screenX/2 - screenX/4;
    int x2 = screenX - screenX/4;
    int y1 = 0;
    int y2 = 0;
    int inc1 = 0;
    int inc2 = 0;
    attron(COLOR_PAIR(PLAYER_ONE));
    for (int i = 0; i < length1; i++){
        char c = s1.at(i);
        mvprintw(y1, x1+inc1++, "%c", c);
        if (c == '\n'){
            y1++;
            inc1 = 0;
        }
    }
    attroff(COLOR_PAIR(PLAYER_ONE));
    attron(COLOR_PAIR(PLAYER_TWO));
    for (int i = 0; i < length2; i++){
        char c = s2.at(i);
        mvprintw(y2, x2+inc2++, "%c", c);
        if (c == '\n'){
            y2++;
            inc2 = 0;
        }
    }
    attroff(COLOR_PAIR(PLAYER_TWO));
}
void drawScreen(){
    if (scoreChanged){
        scoreChanged = false;
        clear();
    }
    drawScore();
    drawPaddles();
    drawMid();
    drawBall();
    refresh();
    this_thread::sleep_for(chrono::milliseconds(SLOW_DOWN_MS));
}
}
