/*Essa struct define uma coordenada horizontal x, vertical y
 * e na direção da tela z.
 */

#ifndef _UTILS_HEADER
#define _UTILS_HEADER 
/*Incluir <math.h> .*/


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
