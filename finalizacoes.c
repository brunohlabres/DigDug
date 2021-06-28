#include <stdio.h>
#include <time.h>
#include "defs.h"

void atualizaFileRanking(tPlayer player){
	char buff[20];
    struct tm *sTm;
    FILE * ranking = fopen("ranking.txt", "a+");

    time_t now = time (0);
    sTm = localtime (&now);

    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
    fprintf (ranking, "%s     %s %ld\n",buff, "Score: ", player.score);
}

