#include <ncurses.h>
#define QUIT_CASE 1
//KEY_UP
//KEY_DOWN
//KEY_LEFT
//KEY_RIGHT
//KEY_RESIZE
int getInput(){
    int c = getch();
    switch (c){
        case 'q': // Catch resize
        return QUIT_CASE;
        case ERR:
        return -1;
        default:
        return c;
        }
}
