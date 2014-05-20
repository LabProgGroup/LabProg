#ifndef _UTILS_HEADER_H_
#define _UTILS_HEADER_H_ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LOOP 100
#define BUFFER_SIZE 1000
#define MAX_DISTANCE_BETWEEN_ENEMIES 20
#define SHOOTABLE_DISTANCE 20 
#define SHOOT_NORM 60
#define MAX_SHIP_SHOTS 50

struct coordinates {
    float x; 
    float y;
    float z;
};
typedef struct coordinates Position;
typedef struct coordinates Velocity;
typedef struct coordinates Dimension;

typedef enum {FALSE, TRUE} BOOL;

typedef enum key {UP, DOWN, RIGHT, LEFT, SPACE, CLICK} Key; 

extern float clockTick;
extern float shotNorm;
extern Dimension defaultCenarioDim;
extern Dimension defaultEnemyDim;

Position spaceTimeEquation(Position initialPosition, Velocity v);
float distance(Position a, Position b);

#endif
