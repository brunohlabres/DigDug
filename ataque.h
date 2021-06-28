#ifndef _ATAQUE_
#define _ATAQUE_
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "defs.h"
#include "monstros.h"

void colisaoAtkMonstro(tMapa *mapa, tPlayer *player, tMonstros *monstros, int auxI, int auxJ);
void limpaAtk(tMapa *mapa);
void atacar(tMapa *mapa, tPlayer *player, tMonstros *monstros);

#endif