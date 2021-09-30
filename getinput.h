#include <ncurses.h>
void getInput(bool *UP, bool *DOWN, bool *LEFT, bool *RIGHT, bool *QUIT, bool *RESIZE){
    int c = getch();
    switch (c){
        case KEY_RESIZE: // Catch resize
        *RESIZE = true;
        break;
        case KEY_UP:
        *UP = true;
        break;
        case KEY_LEFT:
        *LEFT = true;
        break;
        case KEY_RIGHT:
        *RIGHT = true;
        break;
        case KEY_DOWN:
        *DOWN = true;
        break;
        case 'w':
        *UP = true;
        break;
        case 'a':
        *LEFT = true;
        break;
        case 'd':
        *RIGHT = true;
        break;
        case 's':
        *DOWN = true;
        break;
        case 'q':
        *QUIT = true;
        default:
        break;
    }
}
