#ifndef _SHIP_H_
#define _SHIP_H_

#include "utils.h"
#include "shot.h"
#include "configuration.h"

typedef struct ship Ship;
struct ship {
    int life;           
    int focus;
    Position position;  
    Velocity velocity;

    float radius;
};

Ship* createShip(Position position);
void killShip(Ship* sh);
void updateVelocity(Ship *sh, unsigned char key);
void clearVelocity(Ship *sh, unsigned char key);
void updateShipPosition(Ship* sh);

void insideKeeper(Ship *sh, Dimension dimension);
Shot* shootFromShip(Ship *sh, Position aimV, int power);
void gotDamagedShip(Ship* sh, int damage);
BOOL isShipAlive(Ship* sh);
void updateScore(Ship* sh);
void updateFocus(Ship* sh);
void renderShip(Ship* sh);
Velocity getAimV(int x, int y, Ship* sh, int cenx, int ceny);
void renderAim(Ship* sh, Velocity v, int n);
void DrawArc(Position begin, Velocity v, int n);
#endif
