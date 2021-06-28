#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include "defs.h"
#include "inicializacoes.h"
#include "impressoes.h"
#include "logica.h"
#include "monstros.h"
#include "pedra.h"
#include "finalizacoes.h"


int main(){
	int ch;
	tMapa mapa;
	tPlayer player;
	tMonstros monstros;
	tPedra pedras;
	
	initNCurses();
	initCores();
	
	restart: 
	mapa = inicMapa("mapa.txt");
	player = inicPlayer(mapa);
	monstros = inicMonstros(mapa);
	pedras = inicPedras(mapa);

	while ((player.vidas != 0) && (monstros.qtdVivos !=0)){
		ch = getch();
		flushinp(); // limpa buffer
		alteraMapa(&mapa, &player, &monstros, &pedras, ch);
		imprimeMapa(mapa);
		imprimeAlteracoesMapa(mapa, player, monstros);
		imprimeScore(mapa, player);
		imprimeVidas(mapa, player);
		usleep(DELAY);
		imprimeHelp(ch);
		if (ch == 'q'){ // se quitar
			atualizaFileRanking(player); // atualiza ranking
			quitaJogo(ch); // quita
		}
		refresh();
	}

	// player ganhou?
	if (monstros.qtdVivos == 0)
		ch = playerWins(mapa);
	// foi game over?
	else {
		atualizaFileRanking(player);
		ch = gameOver(mapa);
	}
	
	if (ch == 'y')
		goto restart;
	else if (ch == 'q')
		quitaJogo(ch);
	usleep(DELAY);
	endwin();
}