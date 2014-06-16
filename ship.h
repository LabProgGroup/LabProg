#ifndef _SHIP_H_
#define _SHIP_H_

#include "utils.h"
#include "shot.h"

#define INITIAL_VELOCITY 30 
#define MOVING_FACTOR 10   
#define VELOCITY_FACTOR 30
#define MAX_XY_ORIENTATION 25
#define MAX_VELOCITY 2000
#define SHIP_SHOT_VELOCITY 60

typedef struct ship Ship;
struct ship {
    int life;           
    Position position;  
    Velocity velocity;

    float radius;
    // Dimension dimension;
};

extern float traveledDistance;

Ship* createShip(Position position);
void killShip(Ship* sh);
void updateVelocity(Ship *sh, unsigned char key);
void clearVelocity(Ship *sh, unsigned char key);
void updateShipPosition(Ship* sh);

void insideKeeper(Ship *sh, Dimension dimension);
Shot* shootFromShip(Ship *sh, Position aimP, int power);
void gotDamagedShip(Ship* sh, int damage);
BOOL isShipAlive(Ship* sh);
void updateScore(Ship* sh);
void renderShip(Ship* sh);
#endif
