#include "includes.h"
#include "getinput.h"
//KEY_UP
//KEY_DOWN
//KEY_LEFT
//KEY_RIGHT
//KEY_RESIZE
int getInput(){
    int c = getch();
    switch (c){
    case 'q': 
         return QUIT_CASE;
    case 'w':
         return KEY_UP;
    case 'a':
         return KEY_LEFT;
    case 's':
         return KEY_DOWN;
    case 'd':
         return KEY_RIGHT;
    case KEY_UP: case KEY_DOWN: case KEY_LEFT: case KEY_RIGHT: case KEY_RESIZE: case KEY_ESC: case ERR:
         return c;
    default:
         return ERR;
    }   
}
