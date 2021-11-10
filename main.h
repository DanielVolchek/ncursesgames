#ifndef MAIN_H
#define MAIN_H

#include "includes.h"
void runExec(char* exec_file);
void initScreen();
void drawTODO();
void drawScreen();
void showInfo();
void drawTitle();
void drawNames(const char **games, int hightlight);
void selectionLoop(const char **games);
void endScreen();
void chooseGame(int c);

#endif
