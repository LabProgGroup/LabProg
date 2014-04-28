#ifndef _UTILS_HEADER_H_
#define _UTILS_HEADER_H_ 
/*Incluir <math.h> 
 * Ver o que vai ficar aqui desses #include 
 * .*/
#include <stdio.h>
#include <stdlib.h>
/*
Essa struct define uma coordenada horizontal x, vertical y
e na direção da tela z.
*/
struct coordinates {
    float x; 
    float y;
    float z;

};
typedef struct coordinates Position;
typedef struct coordinates Velocity;
typedef struct coordinates Dimension;

#define TRUE 1
#define FALSE 0
#define MAX_LOOP 100

enum key {UP, DOWN, RIGHT, LEFT, SPACE, CLICK}; /* Enum Representando as teclas pressionadas */
typedef enum key Key;

/*
  Recebe duas structs do tipo Position contendo posições (x,y,z) e retorna a distância 
  eucliana.
*/ 
float distance(Position a, Position b);

/*
 Define o tick do relógio em segundos.
 clockTick = 1/fps.
*/
extern float clockTick;

/*
  Define a altura da janela do jogo
*/
extern int ySize;

/*
  Define a largura da janela do jogo
*/
extern int xSize;


/*Recebe a posição da nave e de algum outro objeto (tiro, inimigo) e verifica se ele ainda
 * está na tela, retornando TRUE em case afirmativo e FALSE, caso contrário. */
int isItAtScreen(Position shipP, Position objectP);

/*
  Recebe uma posição So, velocidade v e retorna a nova 
  posição após o tempo de atualização da tela.
 */

Position spaceTimeEquation(Position initialPosition, Velocity v);
#endif
