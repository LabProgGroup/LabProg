#ifndef _SHOT_H_
#define _SHOT_H_

#include "utils.h"

typedef struct {
    Position shotPosition;
    Velocity shotVelocity;
    int damage;
} Shot;

Shot* createShot(Position shotP, Velocity shotV, int damage);
void freeShot(Shot* sh);
void updateShot(Shot* sh);

float computeShotNorm(Shot* sh);

#endif
