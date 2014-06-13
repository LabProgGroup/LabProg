#ifndef _UTILS_HEADER_H_
#define _UTILS_HEADER_H_ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define MAX_LOOP 100
#define BUFFER_SIZE 1000
#define MAX_DISTANCE_BETWEEN_ENEMIES 20
#define MAX_SHIP_SHOTS 50
#define GRAVITY 9.80665
#define DAMAGE_BY_HITTING_ENEMY 50

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
extern Dimension defaultCenarioDim;
extern Dimension defaultEnemyDim;

Position spaceTimeEquation(Position initialPosition, Velocity v);
float distance(Position a, Position b);
Velocity speedTimeEquation(Velocity initialVelocity);
Position createPosition(double x, double  y, double z);
#endif
