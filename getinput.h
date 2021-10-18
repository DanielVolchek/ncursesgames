#include <ncurses.h>
#define QUIT_CASE 10
#define KEY_ESC 27
//KEY_UP
//KEY_DOWN
//KEY_LEFT
//KEY_RIGHT
//KEY_RESIZE
int getInput(){
    int c = getch();
    switch (c){
        case ERR:
        return c;
        case 'q': // Catch resize
        return QUIT_CASE;
        case 'w':
        return KEY_UP;
        case 'a':
        return KEY_LEFT;
        case 's':
        return KEY_DOWN;
        case 'd':
        return KEY_RIGHT;
        case KEY_UP:
        return c;
        case KEY_DOWN:
        return c;
        case KEY_LEFT:
        return c;
        case KEY_RIGHT:
        return c;
        case KEY_RESIZE:
        return c;
        case KEY_ESC:
        return c;
        default:
        return ERR;
    }
}
