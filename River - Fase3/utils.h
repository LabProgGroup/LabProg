#ifndef _UTILS_HEADER_H_
#define _UTILS_HEADER_H_ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "configuration.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define SPLASH_SCREEN 0
#define IN_GAME 1
#define GAME_OVER 2

GLuint idBackground, idShipBase, idShipCream, idEnemy, idWall, idText;

struct coordinates {
    float x; 
    float y;
    float z;
};
typedef struct coordinates Position;
typedef struct coordinates Velocity;
typedef struct coordinates Dimension;

typedef enum {FALSE, TRUE} BOOL;

extern float clockTick;
extern float shipPosition;
extern int gameState;

Position spaceTimeEquation(Position initialPosition, Velocity v);
float distance(Position a, Position b);
Velocity speedTimeEquation(Velocity initialVelocity);
Position createPosition(double x, double  y, double z);
int loadTexture(char *f, GLuint id);
#endif
