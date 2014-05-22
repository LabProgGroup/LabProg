#include <stdio.h>
#include "shot.h"
#include "utils.h"

Shot* createShot(Position shotP, Velocity shotV, int damage) {
    Shot *sh = (Shot*) malloc(sizeof (Shot));
    sh->position = shotP;
    sh->velocity = shotV;
    sh->damage = damage;
    return sh;
}

void freeShot(Shot* sh) {
    if (sh != NULL)
        free(sh);
}

void updateShot(Shot* sh) {
    sh->position = spaceTimeEquation(sh->position, sh->velocity);
    sh->velocity = speedTimeEquation(sh->velocity);
}







