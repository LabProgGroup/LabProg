CFLAGS= -g -Wall -O2 -ansi -pedantic -Wno-unused-result
CC = gcc -g
RM = rm
#-------------------------------------------------

riverraid:  main.o  utils.o cenario.o enemyQueue.o enemy.o ship.o  shot.o shotQueue.o
	$(CC) -lm main.o  utils.o cenario.o enemyQueue.o enemy.o ship.o shot.o shotQueue.o -o riverraid -lm

main.o: main.c utils.h cenario.h enemyQueue.h enemy.h ship.h  shot.h
	$(CC) -c main.c

utils.o: utils.h utils.c
	$(CC) -lm -c utils.c

cenario.o: cenario.h cenario.c enemyQueue.h utils.h ship.h enemy.h 
	$(CC) -c cenario.c

enemyQueue.o: enemyQueue.h enemyQueue.c utils.h enemy.h
	$(CC) -c enemyQueue.c

shotQueue.o: shotQueue.h shotQueue.c utils.h shot.h
	$(CC) -c shotQueue.c

enemy.o: enemy.h enemy.c utils.h shot.h
	$(CC) -lm -c enemy.c

ship.o: ship.h ship.c utils.h shot.h 
	$(CC) -lm -c ship.c

shot.o: shot.h shot.c utils.h
	$(CC) -c shot.c

clean:
	rm *.o *~
