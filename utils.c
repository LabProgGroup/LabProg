#include "utils.h"


/*
  Recebe duas structs do tipo Position contendo posições (x,y,z) e retorna a distância 
  eucliana.
*/ 
float distance(Position a, Position b) { 
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}
