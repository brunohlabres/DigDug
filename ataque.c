#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "defs.h"
#include "monstros.h"

int colisaoAtkMonstro(tMapa *mapa, tPlayer *player, tMonstros *monstros, int auxI, int auxJ){
	int numMonstro;
	switch (player->direcao){
		case DIRECAO_LEFT:
			if (mapa->matriz[auxI][auxJ-2] == CHARMONSTRO){
				numMonstro = achaIndiceMonstro(monstros, auxI, auxJ-2);
				monstros->stun[numMonstro] += STUNADO;
				if (monstros->stun[numMonstro] == EXPLODE){
					mataMonstroComIndice(mapa, monstros, numMonstro);
					player->score += SCORE_MATA_MONSTRO;
				}
				return(TRUE);
			}
			else if (mapa->matriz[auxI+1][auxJ-2] == CHARMONSTRO){
				numMonstro = achaIndiceMonstro(monstros, auxI+1, auxJ-2);
				monstros->stun[numMonstro] += STUNADO;
				if (monstros->stun[numMonstro] == EXPLODE){
					mataMonstroComIndice(mapa, monstros, numMonstro);
					player->score += SCORE_MATA_MONSTRO;
				}
				return(TRUE);
			}
		break;

		case DIRECAO_RIGHT:
			if (mapa->matriz[auxI][auxJ+2] == CHARMONSTRO){
				numMonstro = achaIndiceMonstro(monstros, auxI, auxJ+2);
				monstros->stun[numMonstro] += STUNADO;
				if (monstros->stun[numMonstro] == EXPLODE){
					mataMonstroComIndice(mapa, monstros, numMonstro);
					player->score += SCORE_MATA_MONSTRO;
				}
				return(TRUE);
			}
			else if (mapa->matriz[auxI+1][auxJ+2] == CHARMONSTRO){
				numMonstro = achaIndiceMonstro(monstros, auxI+1, auxJ+2);
				monstros->stun[numMonstro] += STUNADO;
				if (monstros->stun[numMonstro] == EXPLODE){
					mataMonstroComIndice(mapa, monstros, numMonstro);
					player->score += SCORE_MATA_MONSTRO;				
				}
				return(TRUE);
			}
		break;

		case DIRECAO_UP:
			if (mapa->matriz[auxI-1][auxJ] == CHARMONSTRO){
				numMonstro = achaIndiceMonstro(monstros, auxI-1, auxJ);
				monstros->stun[numMonstro] += STUNADO;
				if (monstros->stun[numMonstro] == EXPLODE){
					mataMonstroComIndice(mapa, monstros, numMonstro);
					player->score += SCORE_MATA_MONSTRO;				
				}
				return(TRUE);
			}
			else if (mapa->matriz[auxI-1][auxJ+1] == CHARMONSTRO){
				numMonstro = achaIndiceMonstro(monstros, auxI-1, auxJ+1);
				monstros->stun[numMonstro] += STUNADO;
				if (monstros->stun[numMonstro] == EXPLODE){
					mataMonstroComIndice(mapa, monstros, numMonstro);
					player->score += SCORE_MATA_MONSTRO;
				}
				return(TRUE);
			}
			else if (mapa->matriz[auxI-1][auxJ-1] == CHARMONSTRO){
				numMonstro = achaIndiceMonstro(monstros, auxI-1, auxJ-1);
				monstros->stun[numMonstro] += STUNADO;
				if (monstros->stun[numMonstro] == EXPLODE){
					mataMonstroComIndice(mapa, monstros, numMonstro);
					player->score += SCORE_MATA_MONSTRO;				
				}
				return(TRUE);
			}
		break;

		case DIRECAO_DOWN:
			if (mapa->matriz[auxI+1][auxJ] == CHARMONSTRO){
				numMonstro = achaIndiceMonstro(monstros, auxI+1, auxJ);
				monstros->stun[numMonstro] += STUNADO;
				if (monstros->stun[numMonstro] == EXPLODE){
					mataMonstroComIndice(mapa, monstros, numMonstro);
					player->score += SCORE_MATA_MONSTRO;				
				}
				return(TRUE);
			}
			else if (mapa->matriz[auxI+1][auxJ+1] == CHARMONSTRO){
				numMonstro = achaIndiceMonstro(monstros, auxI+1, auxJ+1);
				monstros->stun[numMonstro] += STUNADO;
				if (monstros->stun[numMonstro] == EXPLODE){
					mataMonstroComIndice(mapa, monstros, numMonstro);
					player->score += SCORE_MATA_MONSTRO;				
				}
				return(TRUE);
			}
			else if (mapa->matriz[auxI+1][auxJ-1] == CHARMONSTRO){
				numMonstro = achaIndiceMonstro(monstros, auxI+1, auxJ-1);
				monstros->stun[numMonstro] += STUNADO;
				if (monstros->stun[numMonstro] == EXPLODE){
					mataMonstroComIndice(mapa, monstros, numMonstro);
					player->score += SCORE_MATA_MONSTRO;				
				}
				return(TRUE);
			}
		break;
	}
	return(FALSE);
}

void limpaAtk(tMapa *mapa){
	int i, j;
	for (i = 0 ; i < mapa->lin ; i++){
		for (j = 0 ; j < mapa->col ; j++){
			if ((mapa->matriz[i][j] == ATK_HORIZONTAL) || (mapa->matriz[i][j] == ATK_VERTICAL)){
				mapa->matriz[i][j] = AR;
			}
		}
	}
}

void atacar(tMapa *mapa, tPlayer *player, tMonstros *monstros){
	int auxI, auxJ, cont = 0;
	
	// lanca ataque
	switch (player->direcao){
		case DIRECAO_UP:
			auxI = player->i-2;
			while((cont < NUM_LINHAS_ATK) && (player->i+auxI != LIM_MAPA_UP) 
			&& (mapa->matriz[auxI][player->j] == AR)){
					mapa->matriz[auxI][player->j] = ATK_VERTICAL;
					if (colisaoAtkMonstro(mapa, player, monstros, auxI, player->j))
						break;		
					auxI--;
					cont++;
			}
		break;

		case DIRECAO_DOWN:
			auxI = player->i+1;
			while((cont < NUM_LINHAS_ATK) && (player->i+auxI != LIM_MAPA_DOWN)
			&& (mapa->matriz[auxI][player->j] == AR)){
					mapa->matriz[auxI][player->j] = ATK_VERTICAL;
					if (colisaoAtkMonstro(mapa, player, monstros, auxI, player->j))
						break;							
					auxI++;
					cont++;
			}
		break;

		case DIRECAO_LEFT:
			auxJ = player->j-2;
			while((cont < NUM_COLUNAS_ATK) && (player->j+auxJ != LIM_MAPA_LEFT)
			&& (mapa->matriz[player->i][auxJ] == AR)){
				mapa->matriz[player->i][auxJ] = ATK_HORIZONTAL;
				if (colisaoAtkMonstro(mapa, player, monstros, player->i, auxJ))
					break;				
				auxJ--;
				cont++;
			}
		break;

		case DIRECAO_RIGHT:
			auxJ = player->j+2;
			while((cont < NUM_COLUNAS_ATK) && (player->j+auxJ != LIM_MAPA_RIGHT)
			&& (mapa->matriz[player->i][auxJ] == AR)){
				mapa->matriz[player->i][auxJ] = ATK_HORIZONTAL;
				if (colisaoAtkMonstro(mapa, player, monstros, player->i, auxJ))
					break;	
				auxJ++;
				cont++;
			}
		break;
	}
}
