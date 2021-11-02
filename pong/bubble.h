//File name:/home/danielvolchek/ncursesgames/pong/bubble.h
//Daniel Volchek
//Section_01

//Code:
#include <iostream>
using namespace std;
string getLetter(int n, int *length){
    *length = 0;
    const char *s[10] ={"  ___      \n / _\"\\  u  \n| / U |/   \n| \\// |,-. \n \\___/(_/  \n  //       \n (__)",
                  "    _\n   /\"|   \n u | |u   \n  \\| |/  \n   |_|   \n _//<,-, \n(__)(_/",
                  "  ____    \n |___\"\\   \n U __) |  \n \\/ __/ \\ \n |_____|u \n <<  //   \n(__)(__)",
                  " _____   \n|___\"/u  \nU_|_ \\/  \n ___) |  \n|____/   \n _// /\\  \n(__)(__)",
                  " _  _    \n| ||\"|   \n| || |_  \n|__   _| \n  /|_|\\  \n u_|||_u \n (__)__)",
                  "  ____    \nU|\"___|u  \n\\|___ \\/  \n  ___) |  \n |____/   \n,-,>>\\,-. \n \\ ) (_/",
                  "   __     \nU /\"/_ u  \n\\| '_ \\/  \n | (_) |  \n  \\___/   \n _// \\_  \n(__) (__)",
                  "  _____  \n |___ \"| \n    / /  \n u// /\\  \n  /_/ U  \n <<>>_   \n(__)__)",
                  "  ___     \nU( \" ) u  \n\\/   \\/   \n| ( ) |   \n \\___/>>  \n  )( (__) \n (__)",
                  "    ___    \n  / _\"\\   \n | (_) |  \n /\\__, |\\ \nU<< |_/ u \n(__) )(   \n    (__)"};
    const int lengths[10] = {77, 64, 74, 68, 68, 74, 74, 67, 71, 75};
    *length = lengths[n];
    return s[n];
}
