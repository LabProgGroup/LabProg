#include <stdio.h>
#include "shot.h"
#include "utils.h"
#include "shotQueue.h"
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

void renderShot(Shot* sh) {
    glPushMatrix();
    glTranslatef(sh->position.x, sh->position.y, -sh->position.z + shipPosition);
    glColor3f(0.5, 0.06, 0.04);
    glutWireSphere(0.3, 50, 50);
    glPopMatrix();
}




