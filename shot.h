#ifndef _SHOT_H_
#define _SHOT_H_

#include "utils.h"

typedef struct {
    Position position;
    Velocity velocity;
    int damage;
} Shot;

Shot* createShot(Position shotP, Velocity shotV, int damage);
void freeShot(Shot* sh);
void updateShot(Shot* sh);

#endif
