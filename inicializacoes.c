#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "inicializacoes.h"
#include "defs.h"


void initNCurses(){
	initscr () ;		   // inicializa a biblioteca ncurses
	raw () ;		   // ler teclas de controle (^C, ^Z, etc)
	nodelay (stdscr, TRUE) ; // leitura não-bloqueante do teclado
	keypad (stdscr, TRUE) ;  // ativa leitura de teclas de setas, Fn, etc
	noecho () ;		   // não escreve as teclas lidas na tela
	curs_set (0) ;	   // esconde o cursor do terminal
 }

void initCores(){
	start_color();	// inicia cores
	init_color(COLOR_YELLOW, 255/0.255, 255/0.255, 153/0.255); // terra 1
	init_pair(1, COLOR_BLACK, COLOR_YELLOW); // terra 2
	init_color(COLOR_BLUE, 255/0.255, 153/0.255, 51/0.255); // terra 1
	init_pair(2, COLOR_RED, COLOR_BLUE); // terra 2
	init_color(COLOR_WHITE, 204/0.255, 102/0.255, 0); // terra 1
	init_pair(3, COLOR_RED, COLOR_WHITE); // terra 3
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK); // terra 3
}

tMapa inicMapa(char * nomeArq){
	FILE * arqMapa;
	tMapa mapa; 

	arqMapa = fopen(nomeArq, "r");

	if (!arqMapa){
		perror("Mapa nao encontrado.");
		endwin();
		exit(1);
	}

	fread(mapa.matriz, NUMLIN*NUMCOL, 1, arqMapa);
	mapa.lin = NUMLIN; //arrumar
	mapa.col = NUMCOL;
	fclose(arqMapa);
	return(mapa);
}

tPlayer inicPlayer(tMapa mapa){
	int i, j;
	tPlayer player;

	player.direcao = DIRECAO_LEFT; // player comeca olhando para a esquerda
	// procura posicao do player no mapa
	player.vidas = 3;
	player.score = 0;
	player.i = -1;
	player.j = -1;
	for (i = 0 ; i < NUMLIN ; i++){
		for (j = 0 ; j < NUMCOL ; j++){
			if (mapa.matriz[i][j] == CHARJOGADOR){
				player.inicialI = i;
				player.inicialJ = j;
			}
		}
	}
	player.i = player.inicialI;
	player.j = player.inicialJ;
	if ((player.i == -1) && (player.j == -1)){
		perror("Jogador nao encontrado.");
		endwin();
		exit(1);
	}

	return (player);
}