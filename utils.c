#include "utils.h"


/*
  Recebe duas structs do tipo Position contendo posições (x,y,z) e retorna a distância 
  eucliana.
*/ 
float distance(Position a, Position b) { 
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}

/*
 Define o tick do relógio em segundos.
 clockTick = 1/fps.
*/
float clockTick = (float) 1/20;

/*Recebe a posição da nave e de algum outro objeto (tiro, inimigo) e verifica se ele ainda
 * está na tela, retornando TRUE em case afirmativo e FALSE, caso contrário. */
int isAtScreen(Position shipP, Position objectP);
