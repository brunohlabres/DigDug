#ifndef _PEDRA_
#define _PEDRA_

#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include "logica.h"
#include "defs.h"

tPedra inicPedras(tMapa mapa);
void pedraCai(tMapa *mapa, tPlayer *player, tMonstros *monstros, tPedra *pedras);
void contagemQuedaPedra(tMapa *mapa, tPlayer *player, tMonstros *monstros, tPedra *pedras);

#endif