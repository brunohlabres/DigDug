#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include "logica.h"
#include "defs.h"

tPedra inicPedras(tMapa mapa){
	int i, j, x;
	tPedra pedras;

	// verifica qtd de monstros no mapa
	pedras.qtd = 0;
	for (i = 0 ; i < mapa.lin ; i++){
		for (j = 0 ; j < mapa.col ; j++){
			if (mapa.matriz[i][j] == PEDRA){
				pedras.qtd++;
			}
		}
	}

	// faz alocacoes de acordo com a qtd de pedras
	pedras.posicaoI = malloc(pedras.qtd*sizeof(short));
	pedras.posicaoJ = malloc(pedras.qtd*sizeof(short));
	pedras.contQueda = malloc(pedras.qtd*sizeof(short));
	pedras.valida = malloc(pedras.qtd*sizeof(short));

	x = 0;
	for (i = 0 ; i < mapa.lin ; i++){
		for (j = 0 ; j < mapa.col ; j++){
			if (mapa.matriz[i][j] == PEDRA){
				pedras.posicaoI[x] = i; 
				pedras.posicaoJ[x] = j; 
				pedras.contQueda[x] = CONT_INIC_QUEDA;
				pedras.valida[x] = SIM;
				x++;
			}
		}
	}

	return (pedras);
}


void pedraCai(tMapa *mapa, tPlayer *player, tMonstros *monstros, tPedra *pedras){
	int i;
	for (i = 0 ; i < pedras->qtd ; i++){
		if (pedras->valida[i] == SIM){
			// PEDRA - PLAYER
			// ve se tem player embaixo da pedra, se tiver ela cai nele
			if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]] == CHARJOGADOR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]-1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]+1] == AR)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					pedras->posicaoI[i]++;
					perdeuVida(mapa, monstros, player);
			}
			// ve se tem player embaixo da pedra, se tiver ela cai nele
			else if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]-1] == CHARJOGADOR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]+1] == AR)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					pedras->posicaoI[i]++;
					perdeuVida(mapa, monstros, player);
			}
			// ve se tem player embaixo da pedra, se tiver ela cai nele
			else if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]+1] == CHARJOGADOR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]-1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]] == AR)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					pedras->posicaoI[i]++;
					perdeuVida(mapa, monstros, player);
			}
			// ve se tem player embaixo da pedra, se tiver ela cai nele
			else if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-2] == CHARJOGADOR)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					pedras->posicaoI[i]++;
					perdeuVida(mapa, monstros, player);
			}
			// ve se tem player embaixo da pedra, se tiver ela cai nele
			else if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+2] == CHARJOGADOR)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					pedras->posicaoI[i]++;
					perdeuVida(mapa, monstros, player);
			}
			// ve se tem player embaixo da pedra, se tiver ela cai nele
			else if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == CHARJOGADOR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					pedras->posicaoI[i]++;
					perdeuVida(mapa, monstros, player);
			}
			////////////////
			else if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == CHARJOGADOR)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					pedras->posicaoI[i]++;
					perdeuVida(mapa, monstros, player);
			}
			// APENAS CAI
			// ve se tem AR embaixo da pedra, se tiver ela cai no espaço vazio
			else if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					pedras->posicaoI[i]++;
			}

			// PEDRA - MONSTRO
			// ve se tem MONSTRO embaixo da pedra, se tiver ela cai nele
			if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]] == CHARMONSTRO) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]-1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]+1] == AR)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					mataMonstro(mapa, monstros, pedras->posicaoI[i]+2,pedras->posicaoJ[i]);
					player->score += SCORE_MONSTRO_ESMAGADO;
					mvprintw(pedras->posicaoI[i]+2,pedras->posicaoJ[i], "%d", SCORE_MONSTRO_ESMAGADO);
					pedras->posicaoI[i]++;
			}
			else if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]-1] == CHARMONSTRO) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]+1] == AR)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					mataMonstro(mapa, monstros, pedras->posicaoI[i]+2,pedras->posicaoJ[i]-1);
					player->score += SCORE_MONSTRO_ESMAGADO;
					mvprintw(pedras->posicaoI[i]+2,pedras->posicaoJ[i]-1, "%d", SCORE_MONSTRO_ESMAGADO);
					pedras->posicaoI[i]++;
			}
			else if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]+1] == CHARMONSTRO) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]-1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+2][pedras->posicaoJ[i]] == AR)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					mataMonstro(mapa, monstros, pedras->posicaoI[i]+2,pedras->posicaoJ[i]+1);
					player->score += SCORE_MONSTRO_ESMAGADO;
					mvprintw(pedras->posicaoI[i]+2,pedras->posicaoJ[i]+1, "%d", SCORE_MONSTRO_ESMAGADO);
					pedras->posicaoI[i]++;
			}
			else if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-2] == CHARMONSTRO)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					mataMonstro(mapa, monstros, pedras->posicaoI[i]+1,pedras->posicaoJ[i]-2);
					player->score += SCORE_MONSTRO_ESMAGADO;
					mvprintw(pedras->posicaoI[i]+1,pedras->posicaoJ[i]-2, "%d", SCORE_MONSTRO_ESMAGADO);
					pedras->posicaoI[i]++;
			}
			else if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR) &&
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+2] == CHARMONSTRO)){
					mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
					mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] = PEDRA;
					mataMonstro(mapa, monstros, pedras->posicaoI[i]+1,pedras->posicaoJ[i]+2);
					player->score += SCORE_MONSTRO_ESMAGADO;
					mvprintw(pedras->posicaoI[i]+1,pedras->posicaoJ[i]+2, "%d", SCORE_MONSTRO_ESMAGADO);
					pedras->posicaoI[i]++;
			}

		}
	}
}

////////
// pedra cai apenas apos um tempo 
void contagemQuedaPedra(tMapa *mapa, tPlayer *player, tMonstros *monstros, tPedra *pedras){
	int i;
	for (i = 0 ; i < pedras->qtd ; i++){
		if (pedras->valida[i] == SIM){
			if (pedras->contQueda[i] == SOME_PEDRA){
				pedras->valida[i] = NAO;
				mapa->matriz[pedras->posicaoI[i]][pedras->posicaoJ[i]] = AR;
			}
			else if(pedras->contQueda[i] <= CAI){
				pedraCai(mapa, player, monstros, pedras);
				pedras->contQueda[i]--;
			}
			else if(pedras->contQueda[i] <= ATIVA_QUEDA)
				pedras->contQueda[i]--;
			else if ((mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]-1] == AR) && 
				(mapa->matriz[pedras->posicaoI[i]+1][pedras->posicaoJ[i]+1] == AR)){
				pedras->contQueda[i] = ATIVA_QUEDA;
			}
		}
	}
}
