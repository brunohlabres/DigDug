#ifndef _IMPRESSOES_
#define _IMPRESSOES_

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include "defs.h"

void imprimeMapa(tMapa mapa);
void imprimeJogador(tPlayer player, int i, int j);
void imprimeMonstro(int i, int j);
void imprimeMonstroStunado(int i, int j);
void imprimeDragao(int i, int j);
void imprimePedra(int i, int j);
void imprimeScore(tMapa mapa, tPlayer player);
void imprimeVidas(tMapa mapa, tPlayer player);
int gameOver(tMapa mapa);
int playerWins(tMapa mapa);
void imprimeAllMonstros(tMonstros monstros);
void imprimeAlteracoesMapa(tMapa mapa, tPlayer player, tMonstros monstros);
void imprimeHelp(int ch);

#endif