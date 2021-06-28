#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include "defs.h"
#include "impressoes.h"
#include "logica.h"

void imprimeMapa(tMapa mapa){	
	int i,j;
	for (i = 0 ; i < NUMLIN ; i++){
		for (j = 0 ; j < NUMCOL ; j++){
			mvprintw(i,j,&mapa.matriz[i][j]);
			if ((mapa.matriz[i][j] == TERRA) && (i < mapa.lin/FAIXASDETERRA)){
				attron(COLOR_PAIR(1));
				mvprintw(i,j,&mapa.matriz[i][j]);
				attroff(COLOR_PAIR(1));
			}
			else if ((mapa.matriz[i][j] == TERRA) && (i >= mapa.lin/FAIXASDETERRA) && (i < mapa.lin-mapa.lin/FAIXASDETERRA)) {
				attron(COLOR_PAIR(2));
				mvprintw(i,j,&mapa.matriz[i][j]);
				attroff(COLOR_PAIR(2));
			}
			else if (mapa.matriz[i][j] == TERRA) {
				attron(COLOR_PAIR(3));
				mvprintw(i,j,&mapa.matriz[i][j]);
				attroff(COLOR_PAIR(3));
			}
		}
	}
}


void imprimeJogador(tPlayer player, int i, int j){
	switch(player.direcao){
		case DIRECAO_LEFT:
			mvprintw(i,j, "_");
			mvprintw(i,j-1, "(");
			mvprintw(i,j+1, "s");
			mvprintw(i-1,j, "\"");
			mvprintw(i-1,j-1, "<");
			mvprintw(i-1,j+1, ")");
			break;
		case DIRECAO_RIGHT:
			mvprintw(i,j, "_");
			mvprintw(i,j-1, "z");
			mvprintw(i,j+1, ")");
			mvprintw(i-1,j, "\"");
			mvprintw(i-1,j-1, "(");
			mvprintw(i-1,j+1, ">");
			break;
		case DIRECAO_UP:
			mvprintw(i,j, "l");
			mvprintw(i,j-1, "(");
			mvprintw(i,j+1, ")");
			mvprintw(i-1,j, " ");
			mvprintw(i-1,j-1, "(");
			mvprintw(i-1,j+1, ")");
			break;
		case DIRECAO_DOWN:
			mvprintw(i,j, " ");
			mvprintw(i,j-1, "(");
			mvprintw(i,j+1, ")");
			mvprintw(i-1,j, "v");
			mvprintw(i-1,j-1, "(");
			mvprintw(i-1,j+1, ")");
			break;
	}
}
//////////////// MONSTROS /////////////
void imprimeMonstro(int i, int j){
	mvprintw(i,j, "W");
	mvprintw(i,j-1, "w");
	mvprintw(i,j+1, "w");
	mvprintw(i-1,j, "-");
	mvprintw(i-1,j-1, "o");
	mvprintw(i-1,j+1, "o");
}

void imprimeMonstroStunado(int i, int j){
	attron(COLOR_PAIR(4));
	mvprintw(i,j, "W");
	mvprintw(i,j-1, "w");
	mvprintw(i,j+1, "w");
	mvprintw(i-1,j, "-");
	mvprintw(i-1,j-1, "x");
	mvprintw(i-1,j+1, "x");
	attroff(COLOR_PAIR(4));
}

void imprimeAllMonstros(tMonstros monstros){
	int x;
	for (x = 0 ; x < monstros.qtd ; x++){
		if (monstros.estado[x] == VIVO){
			if (monstros.stun[x] >= STUNADO){
				imprimeMonstroStunado(monstros.posicaoI[x], monstros.posicaoJ[x]);
			}
			else {
				imprimeMonstro(monstros.posicaoI[x], monstros.posicaoJ[x]);
			}
		}
	}
}
///////////////////////////////////////
void imprimeDragao(int i, int j){
	mvprintw(i,j, "_");
	mvprintw(i,j-1, "d");
	mvprintw(i,j+1, ")");
	mvprintw(i-1,j, "\"");
	mvprintw(i-1,j-1, "{");
	mvprintw(i-1,j+1, "3");
}

void imprimePedra(int i, int j){
	mvprintw(i,j, "#");
	mvprintw(i,j-1, "#");
	mvprintw(i,j+1, "#");
	mvprintw(i-1,j, "#");
	mvprintw(i-1,j-1, "#");
	mvprintw(i-1,j+1, "#");
}

void imprimeScore(tMapa mapa, tPlayer player){
	mvprintw(mapa.lin+2,2, "Score: %ld", player.score);
}

void imprimeVidas(tMapa mapa, tPlayer player){
	mvprintw(mapa.lin+2,15, "Vidas: %ld", player.vidas);
}

int gameOver(tMapa mapa){
	int ch = 0;
	mvprintw(mapa.lin/2,mapa.col/3, "Game Over. Press 'y' to replay.");
	refresh();
	ch = getch();
	while ((ch != 'y') && (ch != 'q')){
		usleep(4000);
		ch = getch();
	}
	return(ch);
}

int playerWins(tMapa mapa){
	int ch = 0;
	mvprintw(mapa.lin/2,mapa.col/3, "You won! Press 'y' to continue.");
	refresh();
	ch = getch();
	while ((ch != 'y') && (ch != 'q')){
		usleep(4000);
		ch = getch();
	}
	return(ch);
}

void imprimeAlteracoesMapa(tMapa mapa, tPlayer player, tMonstros monstros){
	int i, j;

	for (i = 0 ; i < mapa.lin ; i++){
		for (j = 0 ; j < mapa.col ; j++){
			switch (mapa.matriz[i][j]){
				case 'p':
					imprimeJogador(player, i, j);
					break;
				case 'd':
					imprimeDragao(i, j);
					break;
				case '#':
					imprimePedra(i, j);
					break;
			}
		}
	}
	imprimeAllMonstros(monstros);
}

void imprimeHelp(int ch){
	int aux = 0;
	if (ch == 'h'){
		while (aux != 'h'){
			clear();
			mvprintw(0, 0, STRHELP);
			quitaJogo(aux);
			aux = getch();
		}
	}
}