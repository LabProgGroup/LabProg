#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "utils.h"
#include "ship.h"

Ship* createShip(Position position) {
    Ship* newship = malloc(sizeof (Ship));
    newship->life = 100;

    newship->position.x = position.x;
    newship->position.y = position.y;
    newship->position.z = position.z;

    newship->velocity.x = 0;
    newship->velocity.y = 0;
    newship->velocity.z = INITIAL_VELOCITY;
    
    newship->radius = 5.5;
    return newship;
}

void killShip(Ship* sh) {
    free(sh);
}

void updateVelocity(Ship *sh, unsigned char key) {
    switch (key) {
        case 'w':
            if (sh->velocity.y < 0) sh->velocity.y = 0;
            if (sh->velocity.y + MOVING_FACTOR > MAX_XY_ORIENTATION)
                return;
            sh->velocity.y += MOVING_FACTOR;
            break;
        case 's':
            if (sh->velocity.y > 0) sh->velocity.y = 0;
            if (sh->velocity.y - MOVING_FACTOR < -MAX_XY_ORIENTATION)
                return;
            sh->velocity.y -= MOVING_FACTOR;
            break;
        case 'd':
            if (sh->velocity.x < 0) sh->velocity.x = 0;
            if (sh->velocity.x + MOVING_FACTOR > MAX_XY_ORIENTATION)
                return;
            sh->velocity.x += MOVING_FACTOR;
            break;
        case 'a':
            if (sh->velocity.x > 0) sh->velocity.x = 0;
            if (sh->velocity.x - MOVING_FACTOR < -MAX_XY_ORIENTATION)
                return;
            sh->velocity.x -= MOVING_FACTOR;
            break;
        case ' ':
            if (sh->velocity.z + VELOCITY_FACTOR > MAX_VELOCITY)
                return;
            sh->velocity.z += VELOCITY_FACTOR;
            printf("\nvelocity: %f", sh->velocity.z);
            break;
        case 'p':
            if (sh->velocity.z - VELOCITY_FACTOR < INITIAL_VELOCITY)
                return;
            sh->velocity.z -= VELOCITY_FACTOR;
            break;
        case 'm':
            clockTick = (float)1 / 500;
            break;
        case 'k':
            sh->velocity.z = 0;
            break;
    }
}

void clearVelocity(Ship *sh, unsigned char key) {
    switch (key) {
        case 'w':
            if (sh->velocity.y > 0)
                sh->velocity.y = 0;
            break;
        case 's':
            if (sh->velocity.y < 0)
                sh->velocity.y = 0;
            break;
        case 'd':
            if (sh->velocity.x > 0)
                sh->velocity.x = 0;
            break;
        case 'a':
            if (sh->velocity.x < 0)
                sh->velocity.x = 0;
            break;
        case 'm':
            clockTick = (float)1 / 50;
            break;
    }
}

void updateShipPosition(Ship* sh) {
    sh->position = spaceTimeEquation(sh->position, sh->velocity);
}

void updateScore(Ship* sh) {
    // traveledDistance = sh->position.z;
}

void insideKeeper(Ship *sh, Dimension dimension) {
    if (sh->position.x < -dimension.x) {
        sh->position.x = -dimension.x;
        sh->velocity.x = 0;
    }
    else if (sh->position.x > dimension.x) {
        sh->position.x = dimension.x;
        sh->velocity.x = 0;
    }
    if (sh->position.y < -dimension.y) {
        sh->position.y = -dimension.y;
        sh->velocity.y = 0;
    }
    else if (sh->position.y > dimension.y) {
        sh->position.y = dimension.y;
        sh->velocity.y = 0;
    }
}

Shot* shootFromShip(Ship *sh, Position aimP, int power) {
    Shot* newShot;
    Position shotP = sh->position;
    Velocity shotV;
    float firstNorm = sqrt(aimP.x * aimP.x + aimP.y * aimP.y);
    float normC = SHIP_SHOT_NORM / firstNorm;
    float t = aimP.x / SHIP_SHOT_NORM;

    aimP.x = normC * aimP.x;
    aimP.y = normC * aimP.y;



    shotV.x = aimP.x;
    shotV.y = aimP.y; 
    shotV.z = 0;
    newShot = createShot(shotP, shotV, power);
    return newShot;
}

void gotDamagedShip(Ship* sh, int damage) {
    sh->life -= damage;
}

BOOL isShipAlive(Ship* sh) {
    return sh->life > 0;
}

void renderShip(Ship* sh) {
    glPushMatrix();
    glTranslatef(sh->position.x, sh->position.y, -sh->position.z + shipPosition);
    glColor4f(0.2, 0.56, 0., 0.9);
    glutSolidCube(5); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(sh->position.x + 4, sh->position.y, -sh->position.z + shipPosition);
    glColor4f(0.2, 0.56, 1., 0.9);
    glutSolidCube(3); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(sh->position.x - 4, sh->position.y, -sh->position.z + shipPosition);
    glColor4f(1, 0.56, 0., 0.9);
    glutSolidCube(3);    
    glPopMatrix();
}  
