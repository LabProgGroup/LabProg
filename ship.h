#ifndef _SHIP_H_
#define _SHIP_H_

#include "utils.h"
#include "shot.h"
#include "configuration.h"

typedef struct ship Ship;
struct ship {
    int life;           
    Position position;  
    Velocity velocity;

    float radius;
    // Dimension dimension;
};

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
