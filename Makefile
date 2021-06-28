# Bruno Henrique Labres - GRR20163049
CFLAGS =  -fPIC -Wall -g -lncurses 

objs = logica.o impressoes.o inicializacoes.o monstros.o pedra.o ataque.o finalizacoes.o
temp = *.gch
exec = main
 
# regra default (primeira regra)
all: digdug
 
# regras de ligacao
digdug: main.c $(objs)
	gcc main.c $(objs) -o digdug $(CFLAGS)
 
# regras de compilação
ataque.o: ataque.c defs.h 
	gcc -c ataque.c ataque.h defs.h $(CFLAGS) 
logica.o: logica.c defs.h 
	gcc -c logica.c logica.h defs.h $(CFLAGS) 
impressoes.o: impressoes.c defs.h 
	gcc -c impressoes.c impressoes.h defs.h $(CFLAGS) 
inicializacoes.o: inicializacoes.c defs.h 
	gcc -c inicializacoes.c inicializacoes.h defs.h $(CFLAGS) 
monstros.o: monstros.c defs.h 
	gcc -c monstros.c monstros.h defs.h $(CFLAGS) 
pedra.o: pedra.c defs.h 
	gcc -c pedra.c pedra.h defs.h $(CFLAGS) 
finalizacoes.o: finalizacoes.c finalizacoes.h 
	gcc -c finalizacoes.c finalizacoes.h defs.h $(CFLAGS) 

# remove arquivos temporários
clean:
	-rm $(objs) $(temp) *~
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm $(exec)