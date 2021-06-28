#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include "logica.h"
#include "monstros.h"
#include "inicializacoes.h"
#include "pedra.h"
#include "ataque.h"
#include "defs.h"

void trocaPersonagemPorAr(tMapa *mapa, int i, int j){
	mapa->matriz[i][j] = ' ';
	mapa->matriz[i-1][j-1] = ' ';
	mapa->matriz[i-1][j] = ' ';
	mapa->matriz[i-1][j+1] = ' ';
	mapa->matriz[i][j-1] = ' ';
	mapa->matriz[i][j+1] = ' ';
}

void escavar(tMapa *mapa, tPlayer *player){
	mapa->matriz[player->i][player->j] = ' ';
	if (mapa->matriz[player->i-1][player->j-1] == '\'')
		player->score += SCORETERRA;
	mapa->matriz[player->i-1][player->j-1] = ' ';

	if (mapa->matriz[player->i-1][player->j] == '\'')
		player->score += SCORETERRA;
	mapa->matriz[player->i-1][player->j] = ' ';

	if (mapa->matriz[player->i-1][player->j+1] == '\'')
		player->score += SCORETERRA;
	mapa->matriz[player->i-1][player->j+1] = ' ';

	if (mapa->matriz[player->i][player->j-1] == '\'')
		player->score += SCORETERRA;
	mapa->matriz[player->i][player->j-1] = ' ';

	if (mapa->matriz[player->i][player->j+1] == '\'')
		player->score += SCORETERRA;
	mapa->matriz[player->i][player->j+1] = ' ';
}

void colisaoMonstroPlayer(tMapa *mapa, tMonstros *monstros, tPlayer *player){
	if ((mapa->matriz[player->i-1][player->j] == 'm') ||
		(mapa->matriz[player->i-1][player->j+1] == 'm') ||
		(mapa->matriz[player->i-1][player->j-1] == 'm') ||
		(mapa->matriz[player->i][player->j-1] == 'm') ||
		(mapa->matriz[player->i][player->j+1] == 'm') ||
		(mapa->matriz[player->i+1][player->j] == 'm') ||
		(mapa->matriz[player->i+1][player->j+1] == 'm') ||
		(mapa->matriz[player->i+1][player->j-1] == 'm') ||

		(mapa->matriz[player->i-1][player->j-2] == 'm') ||
		(mapa->matriz[player->i-1][player->j+2] == 'm') ||
		(mapa->matriz[player->i][player->j-2] == 'm') ||
		(mapa->matriz[player->i][player->j+2] == 'm') ||
		(mapa->matriz[player->i+1][player->j-2] == 'm') ||
		(mapa->matriz[player->i+1][player->j+2] == 'm') ||
		(mapa->matriz[player->i+1][player->j] == 'm') ||
		(mapa->matriz[player->i+1][player->j-1] == 'm') ||
		(mapa->matriz[player->i+1][player->j+1] == 'm')){
		

			perdeuVida(mapa, monstros, player);
	}
}

void perdeuVida(tMapa *mapa, tMonstros *monstros, tPlayer *player){
	player->vidas--;
	mapa->matriz[player->i][player->j] = AR;
	player->i = player->inicialI;
	player->j = player->inicialJ;
	mapa->matriz[player->i][player->j] = CHARJOGADOR;
	respawnaMonstros(mapa, monstros);
	if (player->vidas != 0){
		mvprintw(mapa->lin/2,mapa->col/3, "You're dead. But it isn't over.");
		refresh();
		sleep(2);
	}
}

void quitaJogo(int ch){
	if (ch == 'q'){
		endwin();
		exit(1);
	}
}

int validaMovimentoPlayer(tPlayer *player, tPedra *pedras, int ch){
	int i;
	// confere limites do mapa
	switch (ch){
		case KEY_UP:
			if (player->i == LIM_MAPA_UP)
				return(FALSE);
			// confere se n vai sobrepor alguma pedra
			for (i = 0 ; i < pedras->qtd ; i++){
				if (pedras->valida[i] == NAO)
					break;
				if ((player->i-2 == pedras->posicaoI[i]) && (player->j == pedras->posicaoJ[i]))
					return(FALSE);
				if ((player->i-2 == pedras->posicaoI[i]) && (player->j+1 == pedras->posicaoJ[i]))
					return(FALSE);
				if ((player->i-2 == pedras->posicaoI[i]) && (player->j-1 == pedras->posicaoJ[i]))
					return(FALSE);
				if ((player->i-2 == pedras->posicaoI[i]) && (player->j+2 == pedras->posicaoJ[i]))
					return(FALSE);
				if ((player->i-2 == pedras->posicaoI[i]) && (player->j-2 == pedras->posicaoJ[i]))
					return(FALSE);
			}
		break;

		case KEY_DOWN:
			if (player->i == LIM_MAPA_DOWN)
				return(FALSE);
			// confere se n vai sobrepor alguma pedra
			for (i = 0 ; i < pedras->qtd ; i++){
				if (pedras->valida[i] == NAO)
					break;
				if ((player->i+2 == pedras->posicaoI[i]) && (player->j == pedras->posicaoJ[i]))
					return(FALSE);
				if ((player->i+2 == pedras->posicaoI[i]) && (player->j+1 == pedras->posicaoJ[i]))
					return(FALSE);
				if ((player->i+2 == pedras->posicaoI[i]) && (player->j-1 == pedras->posicaoJ[i]))
					return(FALSE);
				if ((player->i+2 == pedras->posicaoI[i]) && (player->j+2 == pedras->posicaoJ[i]))
					return(FALSE);
				if ((player->i+2 == pedras->posicaoI[i]) && (player->j-2 == pedras->posicaoJ[i]))
					return(FALSE);
			}
		break;

		case KEY_LEFT:
			if (player->j == LIM_MAPA_LEFT)
				return(FALSE);
			// confere se n vai sobrepor alguma pedra
			for (i = 0 ; i < pedras->qtd ; i++){
				if (pedras->valida[i] == NAO)
					break;
				if ((player->i == pedras->posicaoI[i]) && (player->j-3 == pedras->posicaoJ[i]))
					return(FALSE);
				if ((player->i-1 == pedras->posicaoI[i]) && (player->j-3 == pedras->posicaoJ[i]))
					return(FALSE);
				if ((player->i+1 == pedras->posicaoI[i]) && (player->j-3 == pedras->posicaoJ[i]))
					return(FALSE);
			}
		break;

		case KEY_RIGHT:
			if (player->j == LIM_MAPA_RIGHT)
				return(FALSE);
			// confere se n vai sobrepor alguma pedra
			for (i = 0 ; i < pedras->qtd ; i++){
				if (pedras->valida[i] == NAO)
					break;
				if ((player->i == pedras->posicaoI[i]) && (player->j+3 == pedras->posicaoJ[i]))
					return(FALSE);
				if ((player->i-1 == pedras->posicaoI[i]) && (player->j+3 == pedras->posicaoJ[i]))
					return(FALSE);
				if ((player->i+1 == pedras->posicaoI[i]) && (player->j+3 == pedras->posicaoJ[i]))
					return(FALSE);
			}
		break;
	}

	return(TRUE);

}

void alteraMapa(tMapa *mapa, tPlayer *player, tMonstros *monstros, tPedra *pedras, int ch){
		limpaAtk(mapa);
		moveMonstro(mapa, monstros);
		colisaoMonstroPlayer(mapa, monstros, player);
		contagemQuedaPedra(mapa, player, monstros, pedras);
		switch (ch){
			case KEY_UP:
				if (!validaMovimentoPlayer(player, pedras, ch))
					break;
				escavar(mapa, player);
				player->direcao = DIRECAO_UP;
				player->i--;
				mapa->matriz[player->i][player->j] = 'p';
				break;
			case KEY_DOWN:
				if (!validaMovimentoPlayer(player, pedras, ch))
					break;
				escavar(mapa, player);
				player->direcao = DIRECAO_DOWN;
				player->i++;
				mapa->matriz[player->i][player->j] = 'p';
				break;
			case KEY_LEFT:
				if (!validaMovimentoPlayer(player, pedras, ch))
					break;
				escavar(mapa, player);
				player->direcao = DIRECAO_LEFT;
				player->j--;
				mapa->matriz[player->i][player->j] = 'p';
				break;
			case KEY_RIGHT:
				if (!validaMovimentoPlayer(player, pedras, ch))
					break;
				escavar(mapa, player);
				player->direcao = DIRECAO_RIGHT;
				player->j++;
				mapa->matriz[player->i][player->j] = 'p';
				break;
			case KEY_ATK:
				atacar(mapa, player, monstros);
				break;
	}
}