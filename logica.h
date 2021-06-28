#ifndef _LOGICA_
#define _LOGICA_

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "monstros.h"
#include "inicializacoes.h"
#include "ataque.h"
#include "pedra.h"
#include "defs.h"

void trocaPersonagemPorAr(tMapa *mapa, int i, int j);
void escavar(tMapa *mapa, tPlayer *player);
void colisaoMonstroPlayer(tMapa *mapa, tMonstros *monstros, tPlayer *player);
void perdeuVida(tMapa *mapa, tMonstros *monstros, tPlayer *player);
void quitaJogo(int ch);
int validaMovimentoPlayer(tPlayer *player, tPedra *pedras, int ch);
void alteraMapa(tMapa *mapa, tPlayer *player, tMonstros *monstros, tPedra *pedras, int ch);
void colisaoPedraPlayer(tMapa *mapa, tPlayer *player);

#endif