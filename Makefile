CFLAGS= -g -Wall -O2 -ansi -pedantic -Wno-unused-result
CC = gcc -g
RM = rm
#-------------------------------------------------

riverraid:  main.o  utils.o cenario.o queue.o enemy.o ship.o  shot.o
	$(CC) main.o  utils.o cenario.o queue.o enemy.o ship.o shot.o -o riverraid

main.o: main.c utils.h cenario.h queue.h enemy.h ship.h  shot.h
	$(CC) -c main.c

utils.o: utils.h utils.c
	$(CC) -lm -c utils.c

cenario.o: cenario.h cenario.c queue.h utils.h ship.h enemy.h
	$(CC) -c cenario.c

queue.o: queue.h queue.c utils.h enemy.h
	$(CC) -c queue.c

enemy.o: enemy.h enemy.c utils.h shot.h
	$(CC) -lm -c enemy.c

ship.o: ship.h ship.c utils.h shot.h 
	$(CC) -lm -c ship.c

shot.o: shot.h shot.c utils.h
	$(CC) -c shot.c

clean:
	rm *.o *~