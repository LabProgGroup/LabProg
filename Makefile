<<<<<<< HEAD
CFLAGS=-Wall -g -Wno-deprecated
LDFLAGS= -lglut -lGLU -lGL -v -lm

#INCLUDE_PATHS= -I/usr/local/include -I/opt/X11/include
#LIBRARY_PATHS= -L/usr/local/lib -I/opt/X11/lib
#LINKER_FLAGS = -framework OpenGL -lGLUT

=======
CFLAGS= -g -Wall -O2 -ansi -pedantic -Wno-unused-result
CC = gcc -g
LDFLAGS= -lglut -lGLU -lGL
>>>>>>> 669e79b207597a847346e34e0c34e4027ae9465d
RM = rm
#-------------------------------------------------

all: riverraid
	./riverraid

riverraid:  main.o  utils.o cenario.o enemyQueue.o enemy.o ship.o  shot.o shotQueue.o
<<<<<<< HEAD
	$(CC) -lm main.o  utils.o cenario.o enemyQueue.o enemy.o ship.o shot.o shotQueue.o -o riverraid $(LDFLAGS) 
=======
	$(CC) -lm main.o  utils.o cenario.o enemyQueue.o enemy.o ship.o shot.o shotQueue.o -o riverraid $(LDFLAGS) -lm
>>>>>>> 669e79b207597a847346e34e0c34e4027ae9465d

main.o: main.c utils.h cenario.h enemyQueue.h enemy.h ship.h  shot.h
	$(CC) -c main.c 

utils.o: utils.h utils.c
	$(CC) -c utils.c

cenario.o: cenario.h cenario.c enemyQueue.h utils.h ship.h enemy.h 
	$(CC) -c cenario.c 

enemyQueue.o: enemyQueue.h enemyQueue.c utils.h enemy.h
	$(CC) -c enemyQueue.c

shotQueue.o: shotQueue.h shotQueue.c utils.h shot.h
	$(CC) -c shotQueue.c

enemy.o: enemy.h enemy.c utils.h shot.h
	$(CC) -c enemy.c

ship.o: ship.h ship.c utils.h shot.h 
	$(CC) -c ship.c

shot.o: shot.h shot.c utils.h
	$(CC) -c shot.c

clean:
	rm *.o *~
