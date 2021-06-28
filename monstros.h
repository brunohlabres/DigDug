#ifndef _MONSTROS_
#define _MONSTROS_
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "defs.h"

tMonstros inicMonstros(tMapa mapa);
int achaIndiceMonstro(tMonstros *monstros, int posI, int posJ);
void mataMonstro(tMapa *mapa, tMonstros *monstros, int monstroI, int monstroJ);
void mataMonstroComIndice(tMapa *mapa, tMonstros *monstros, int numMonstro);
void moveMonstro(tMapa *mapa, tMonstros *monstros);
short novaDirecaoMonstro(tMapa *mapa, short direcaoAntiga, short i, short j);
void respawnaMonstros(tMapa *mapa, tMonstros *monstros);

#endif