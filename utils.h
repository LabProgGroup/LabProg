#ifndef _UTILS_HEADER_H_
#define _UTILS_HEADER_H_ 
/*Incluir <math.h> 
 * Ver o que vai ficar aqui desses #include 
 * .*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
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

#define TRUE 1
#define FALSE 0

/*
  Recebe duas structs do tipo Position contendo posições (x,y,z) e retorna a distância 
  eucliana.
*/ 
float distance(Position a, Position b);
 




#endif
