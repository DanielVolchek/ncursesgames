//File name:/home/danielvolchek/ncursesgames/main.cpp
//Daniel Volchek
//Section_01

//Code:
#include <iostream>
#include "pong/pong.h"
#include "snake/snake.h"
using namespace std;

int main(){
   int n;
   cout << "1 for pong, 2 for snake" << endl;
   while (n != 0){
   cin >> n;
   if (n == 1)
    pong::runGame();
   else if (n == 2){
    snake::runGame();
   }
   }
   return 0;
}
