#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include "defs.h"
#include "monstros.h"
#include "logica.h"

tMonstros inicMonstros(tMapa mapa){
	int i, j, x;
	tMonstros monstros;

	// verifica qtd de monstros no mapa
	monstros.qtd = 0;
	for (i = 0 ; i < mapa.lin ; i++){
		for (j = 0 ; j < mapa.col ; j++){
			if (mapa.matriz[i][j] == CHARMONSTRO){
				monstros.qtd++;
			}
		}
	}
	monstros.qtdVivos = monstros.qtd;

	// faz alocacoes de acordo com a qtd de monstros
	monstros.estado = malloc(monstros.qtd*sizeof(short));
	monstros.posicaoI = malloc(monstros.qtd*sizeof(short));
	monstros.posicaoJ = malloc(monstros.qtd*sizeof(short));
	// posicoes iniciais dos monstros
	monstros.iInicial = malloc(monstros.qtd*sizeof(short));
	monstros.jInicial = malloc(monstros.qtd*sizeof(short));

	monstros.direcao = malloc(monstros.qtd*sizeof(short));
	monstros.stun = malloc(monstros.qtd*sizeof(short));

	for (i = 0 ; i < monstros.qtd ; i++){
		monstros.estado[i] = VIVO; //monstros comecam vivos
		monstros.direcao[i] = DIRECAO_UP; //comecam "olhando" para a esquerda
		monstros.stun[i] = SEM_STUN; //nao comeca stunado
	}

	x = 0;
	for (i = 0 ; i < mapa.lin ; i++){
		for (j = 0 ; j < mapa.col ; j++){
			if (mapa.matriz[i][j] == CHARMONSTRO){
				monstros.posicaoI[x] = i; 
				monstros.posicaoJ[x] = j; 
				monstros.iInicial[x] = i;
				monstros.jInicial[x] = j;
				x++;
			}
		}
	}

	return (monstros);
}

int achaIndiceMonstro(tMonstros *monstros, int posI, int posJ){
	int i;

	for (i = 0 ; i < monstros->qtd ; i++){
		if ((monstros->posicaoI[i] == posI) && (monstros->posicaoJ[i] == posJ))
			return (i);
	}
	return(FALSE);
}

void mataMonstro(tMapa *mapa, tMonstros *monstros, int monstroI, int monstroJ){
	int i, numMonstro;
	for (i = 0 ; i < monstros->qtd ; i++){
		if ((monstros->posicaoI[i] == monstroI) && (monstros->posicaoJ[i] == monstroJ))
			numMonstro = i;
	}
	monstros->qtdVivos--;
	mapa->matriz[monstros->posicaoI[numMonstro]][monstros->posicaoJ[numMonstro]] = AR;
	monstros->estado[numMonstro] = MORTO;
}

// quando ja tem o indice
void mataMonstroComIndice(tMapa *mapa, tMonstros *monstros, int numMonstro){
	monstros->qtdVivos--;
	mapa->matriz[monstros->posicaoI[numMonstro]][monstros->posicaoJ[numMonstro]] = AR;
	monstros->estado[numMonstro] = MORTO;
}

// monstro vai olhar onde ele pode andar
void moveMonstro(tMapa *mapa, tMonstros *monstros){
	int i, j, x;
	for (x = 0 ; x < monstros->qtd ; x++){
		i = monstros->posicaoI[x];
		j = monstros->posicaoJ[x];
		// se stunado n move
		if ((monstros->stun[x] == SEM_STUN) && (monstros->estado[x] == VIVO)){
			switch(monstros->direcao[x]){
				case DIRECAO_LEFT:
					// verifica se pode andar para a esquerda
					if ((mapa->matriz[i-1][j-2] == AR) && (mapa->matriz[i][j-2] == AR) 
						&& (mapa->matriz[i][j-2] != LIM_MAPA_LEFT)){
						trocaPersonagemPorAr(mapa, i, j);
						mapa->matriz[i][j-1] = CHARMONSTRO;
						monstros->posicaoJ[x]--;
					}
					else {
						monstros->direcao[x] = novaDirecaoMonstro(mapa, *monstros->direcao, *monstros->posicaoI, *monstros->posicaoJ);
					}
					break;
				case DIRECAO_RIGHT:
					if ((mapa->matriz[i-1][j+2] == AR) && (mapa->matriz[i][j+2] == AR) 
						&& (mapa->matriz[i][j+2] != LIM_MAPA_RIGHT)){
						trocaPersonagemPorAr(mapa, i, j);
						mapa->matriz[i][j+1] = CHARMONSTRO;
						monstros->posicaoJ[x]++;
					}
					else {
						monstros->direcao[x] = novaDirecaoMonstro(mapa, *monstros->direcao,  *monstros->posicaoI, *monstros->posicaoJ);
					}
					break;
				case DIRECAO_DOWN:
					if ((mapa->matriz[i+1][j-1] == AR) && (mapa->matriz[i+1][j+1] == AR) 
					&& (mapa->matriz[i+1][j] == AR) && (mapa->matriz[i+1][j] != LIM_MAPA_DOWN)){
						trocaPersonagemPorAr(mapa, i, j);
						mapa->matriz[i+1][j] = CHARMONSTRO;
						monstros->posicaoI[x]++;
					}
					else {
						monstros->direcao[x] = novaDirecaoMonstro(mapa, *monstros->direcao,  *monstros->posicaoI, *monstros->posicaoJ);
					}
					break;	
				case DIRECAO_UP:
					if ((mapa->matriz[i-2][j-1] == AR) && (mapa->matriz[i-2][j+1] == AR) 
						&& (mapa->matriz[i-2][j] == AR) && (mapa->matriz[i-2][j] != LIM_MAPA_UP)){
						trocaPersonagemPorAr(mapa, i, j);	
						mapa->matriz[i-1][j] = CHARMONSTRO;	
						monstros->posicaoI[x]--;		
					}
					else {
						monstros->direcao[x] = novaDirecaoMonstro(mapa, *monstros->direcao,  *monstros->posicaoI, *monstros->posicaoJ);
					}
					break;	
			}
		}
	}
}

short novaDirecaoMonstro(tMapa *mapa, short direcaoAntiga, short i, short j){
	srand ( time(NULL) );
	int r = rand() % 3;
	switch (direcaoAntiga){
		case DIRECAO_RIGHT:
			switch (r){
				case 0:
					// tenta down
					return(DIRECAO_DOWN);
					break;
				case 1:
					// tenta left
					return(DIRECAO_LEFT);
					break;
				case 2:
					//tenta up
					return(DIRECAO_UP);
					break;
			}
			break;
		case DIRECAO_LEFT:
			switch (r){
				case 0:
					// tenta down
					return(DIRECAO_DOWN);
					break;
				case 2:
					// tenta right
					return(DIRECAO_RIGHT);
					break;
				case 3:
					//tenta up
					return(DIRECAO_UP);
					break;
			}
			break;
		case DIRECAO_UP:
			switch (r){
				case 0:
					// tenta down
					return(DIRECAO_DOWN);
					break;
				case 1:
					// tenta right
					return(DIRECAO_RIGHT);
					break;
				case 2:
					// tenta left
					return(DIRECAO_LEFT);
					break;
			}
			break;
		case DIRECAO_DOWN:
			switch (r){
				case 0:
					// tenta right
					return(DIRECAO_RIGHT);
					break;
				case 1:
					// tenta left
					return(DIRECAO_LEFT);
					break;
				case 2:
					//tenta up
					return(DIRECAO_UP);
					break;
			}
			break;
	}
	return (direcaoAntiga);
}

// quando o player morre, respawna monstros
void respawnaMonstros(tMapa *mapa, tMonstros *monstros){
	int i, j;

	for (i = 0 ; i < mapa->lin ; i++){
		for (j = 0 ; j < mapa->col ; j++){
			if (mapa->matriz[i][j] == CHARMONSTRO){
				mapa->matriz[i][j] = ' ';
			}
		}
	}	

	for (i = 0 ; i < monstros->qtd ; i++){
		monstros->posicaoI[i] = monstros->iInicial[i]; 
		monstros->posicaoJ[i] = monstros->jInicial[i]; 
	}	
}