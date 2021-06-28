#ifndef _INIC_
#define _INIC_
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "defs.h"

void initNCurses();
void initCores();
tMapa inicMapa(char * nomeArq);
tPlayer inicPlayer(tMapa mapa);

#endif