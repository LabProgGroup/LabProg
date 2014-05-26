#ifndef _SHIP_H_
#define _SHIP_H_

#include "utils.h"
#include "shot.h"

#define INITIAL_VELOCITY 10 
#define MOVING_FACTOR 2    
#define VELOCITY_FACTOR 10
#define MAX_XY_ORIENTATION 15
#define MAX_VELOCITY 100
#define SHIP_SHOT_VELOCITY 60

typedef struct ship Ship;
struct ship {
    int life;           
    Position position;  
    Velocity velocity;

    Dimension dimension;
};

extern float traveledDistance;

Ship* createShip(Position position);
void killShip(Ship* sh);
void updateVelocity(Ship *sh, Key key);
void updateShipPosition(Ship* sh);

void insideKeeper(Ship *sh, Dimension dimension);
Shot* shootFromShip(Position aimP, Position shipP, int power);
void gotDamagedShip(Ship* sh, int damage);
BOOL isShipAlive(Ship* sh);
void updateScore(Ship* sh);

#endif
