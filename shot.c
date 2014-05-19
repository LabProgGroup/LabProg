#include <stdio.h>
#include "shot.h"
#include "utils.h"

Shot* createShot(Position shotP, Velocity shotV, int damage) {
    Shot *sh = (Shot*) malloc(sizeof (Shot));
    sh->shotPosition = shotP;
    sh->shotVelocity = shotV;
    sh->damage = damage;
    return sh;
}

void freeShot(Shot* sh) {
    if (sh != NULL)
        free(sh);
}

void updateShot(Shot* sh) {
    sh->shotPosition = spaceTimeEquation(sh->shotPosition, sh->shotVelocity);
    computeShotNorm(sh);
    
}

float computeShotNorm(Shot* sh) {
    shotNorm = sqrt(sh->shotVelocity.x*sh->shotVelocity.x + sh->shotVelocity.y*sh->shotVelocity.y + sh->shotVelocity.z*sh->shotVelocity.z);
    return shotNorm;
}






