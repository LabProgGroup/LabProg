#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "utils.h"
#include "ship.h"

float savedVelocity = 0;

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
        case '8':
            if (sh->velocity.y < 0) sh->velocity.y = 0;
            if (sh->velocity.y + MOVING_FACTOR > MAX_XY_ORIENTATION)
                return;
            sh->velocity.y += MOVING_FACTOR;
            break;
        case '5':
            if (sh->velocity.y > 0) sh->velocity.y = 0;
            if (sh->velocity.y - MOVING_FACTOR < -MAX_XY_ORIENTATION)
                return;
            sh->velocity.y -= MOVING_FACTOR;
            break;
        case '6':
            if (sh->velocity.x < 0) sh->velocity.x = 0;
            if (sh->velocity.x + MOVING_FACTOR > MAX_XY_ORIENTATION)
                return;
            sh->velocity.x += MOVING_FACTOR;
            break;
        case '4':
            if (sh->velocity.x > 0) sh->velocity.x = 0;
            if (sh->velocity.x - MOVING_FACTOR < -MAX_XY_ORIENTATION)
                return;
            sh->velocity.x -= MOVING_FACTOR;
            break;
        case ' ':
            if (sh->velocity.z + VELOCITY_FACTOR > MAX_VELOCITY)
                return;
            sh->velocity.z += VELOCITY_FACTOR;
            break;
        case 'p':
            if (sh->velocity.z - VELOCITY_FACTOR < INITIAL_VELOCITY)
                return;
            sh->velocity.z -= VELOCITY_FACTOR;
            break;
        case 'm':
            savedVelocity = sh->velocity.z;
            sh->velocity.z = INITIAL_VELOCITY;
            break;
        case 'k':
            sh->velocity.z = 0;
            break;
    }
}

void clearVelocity(Ship *sh, unsigned char key) {
    switch (key) {
        case '8':
            if (sh->velocity.y > 0)
                sh->velocity.y = 0;
            break;
        case '5':
            if (sh->velocity.y < 0)
                sh->velocity.y = 0;
            break;
        case '6':
            if (sh->velocity.x > 0)
                sh->velocity.x = 0;
            break;
        case '4':
            if (sh->velocity.x < 0)
                sh->velocity.x = 0;
            break;
        case 'm':
            sh->velocity.z = savedVelocity;
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
    if (sh->position.x < -dimension.x / 2) {
        sh->position.x = -dimension.x / 2;
        sh->velocity.x = 0;
    }
    else if (sh->position.x > dimension.x / 2) {
        sh->position.x = dimension.x / 2;
        sh->velocity.x = 0;
    }
    if (sh->position.y < -dimension.y / 2) {
        sh->position.y = -dimension.y / 2;
        sh->velocity.y = 0;
    }
    else if (sh->position.y > dimension.y / 2) {
        sh->position.y = dimension.y / 2;
        sh->velocity.y = 0;
    }
}

Shot* shootFromShip(Ship *sh, Position aimP, int power) {
    Shot* newShot;
    Position shotP = sh->position;
    Velocity shotV;
    shotV.x = aimP.x;
    shotV.y = aimP.y; 
    shotV.z = sh->velocity.z + sqrt(SHIP_SHOT_VELOCITY * SHIP_SHOT_VELOCITY - (shotV.x * shotV.x + shotV.y * shotV.y));
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
