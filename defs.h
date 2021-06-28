#ifndef _DEFS_
#define _DEFS_

#define NUMLIN 25
#define NUMCOL 119
#define DELAY 5000
#define CHARJOGADOR 'p'
#define CHARMONSTRO 'm'
#define AR ' '
#define TERRA '\''
#define PEDRA '#'
#define ATK_HORIZONTAL '-'
#define ATK_VERTICAL '|'
#define DIRECAO_UP 1
#define DIRECAO_DOWN 2
#define DIRECAO_LEFT 3
#define DIRECAO_RIGHT 4
#define LIM_MAPA_UP 1
#define LIM_MAPA_DOWN NUMLIN-1
#define LIM_MAPA_LEFT 1
#define LIM_MAPA_RIGHT NUMCOL-2
#define VIVO 1
#define MORTO 0
#define SIM 1
#define NAO 0
#define FAIXASDETERRA 3
#define CONT_INIC_QUEDA 20
#define ATIVA_QUEDA CONT_INIC_QUEDA-1
#define CAI 0
#define SOME_PEDRA -20
#define SCORETERRA 5
#define SCORE_MONSTRO_ESMAGADO 500
#define SCORE_MATA_MONSTRO 500
#define NUM_LINHAS_ATK 6
#define NUM_COLUNAS_ATK 9
#define KEY_ATK 'z'
#define SEM_STUN 0
#define STUNADO 1
#define EXPLODE 4

typedef struct{
	char matriz[NUMLIN][NUMCOL];
	int lin;
	int col;
} tMapa;

typedef struct{
	int i;
	int j;
	int inicialI;
	int inicialJ;
	short direcao;
	short vidas;
	long int score;
} tPlayer;

typedef struct{
	short qtd;
	short qtdVivos;
	short *estado;
	short *posicaoI;
	short *posicaoJ;
	short *iInicial;
	short *jInicial;
	short *direcao;
	short *stun;
} tMonstros;

typedef struct{
	short qtd;
	short *valida;
	short *contQueda;
	short *posicaoI;
	short *posicaoJ;
} tPedra;

/* 
o vetor de flags ajuda a mapear os inimigos, para cada inimigo ele contem:
- vivo ou n?
- posicao em i
- posicao em j
- direcao em q o inimigo esta olhando
- se esta no modo ghost ou n
- se ele esta inflando ou nao e em que nivel de inflado

*/

////// HELP ////////
#define STRHELP "Dig Dug\n\nO objetivo deste jogo eh lutar pela sua sobrevivencia eliminando os fantasmas que assombram o subsolo. Navegue pelo mapa com as setas, cavando o subsolo e ganhando pontos.Ataque seus inimigos com a tecla 'z'. Ao serem atacados, eles são stunados e, depois de ataques continuos, mortos. Você pode usar as pedras, derrubando-as sobre as criaturas para derrotá-las, assim que as pedras perdem apoio do chão, elas entram em contagem regressiva e então caem, matando o infeliz que estiver em seu caminho (seja você ou os fantasmas). Seu personagem pode segurar a pedra, mas apenas se ele estiver perfeitamente alinhado com ela quando cavar, e se sair desta posição a pedra vai cair sobre ele da mesma forma. Use isto para abater os fantasmas com diferentes estratégias.\n\nPressione 'h' para fechar esta janela."

#endif