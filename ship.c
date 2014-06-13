#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "utils.h"
#include "ship.h"

float traveledDistance = 0;

Ship* createShip(Position position) {
    Ship* newship = malloc(sizeof (Ship));
    newship->life = 100;

    newship->position.x = position.x;
    newship->position.y = position.y;
    newship->position.z = position.z;

    newship->velocity.x = 0;
    newship->velocity.y = 0;
    newship->velocity.z = INITIAL_VELOCITY;
    
    return newship;
}

void killShip(Ship* sh) {
    free(sh);
}

void updateVelocity(Ship *sh, Key key) {
    switch (key) {
        case UP:
            if (sh->velocity.y + MOVING_FACTOR > MAX_XY_ORIENTATION)
                return;
            sh->velocity.y += MOVING_FACTOR;
            break;
        case DOWN:
            if (sh->velocity.y - MOVING_FACTOR < -MAX_XY_ORIENTATION)
                return;
            sh->velocity.y -= MOVING_FACTOR;
            break;
        case RIGHT:
            if (sh->velocity.x + MOVING_FACTOR > MAX_XY_ORIENTATION)
                return;
            sh->velocity.x += MOVING_FACTOR;
            break;
        case LEFT:
            if (sh->velocity.x - MOVING_FACTOR < -MAX_XY_ORIENTATION)
                return;
            sh->velocity.x -= MOVING_FACTOR;
            break;
        case SPACE:
            if (sh->velocity.z + VELOCITY_FACTOR > MAX_VELOCITY)
                return;
            sh->velocity.z += VELOCITY_FACTOR;
            break;
        default:
            sh->velocity.x = 0;
            sh->velocity.y = 0;
            sh->velocity.z = INITIAL_VELOCITY;
            break;
    }
}

void updateShipPosition(Ship* sh) {
    sh->position = spaceTimeEquation(sh->position, sh->velocity);
}

void updateScore(Ship* sh) {
    traveledDistance = sh->position.z;
}

void insideKeeper(Ship *sh, Dimension dimension) {
    if (sh->position.x < 0) {
        sh->position.x = 0;
        sh->velocity.x = 0;
    }
    else if (sh->position.x > dimension.x) {
        sh->position.x = dimension.x;
        sh->velocity.x = 0;
    }
    if (sh->position.y < 0) {
        sh->position.y = 0;
        sh->velocity.y = 0;
    }
    else if (sh->position.y > dimension.y) {
        sh->position.y = dimension.y;
        sh->velocity.y = 0;
    }
}

Shot* shootFromShip(Position aimP, Position shipP, int power) {
    Shot* newShot;
    Position shotP = shipP;
    Velocity shotV;
    shotV.x = aimP.x - shipP.x;
    shotV.y = aimP.y - shipP.y;
    shotV.z = sqrt(SHIP_SHOT_VELOCITY * SHIP_SHOT_VELOCITY - shotV.x * shotV.x - shotV.y * shotV.y); 
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
    glTranslatef(sh->position.x, sh->position.y, 0);
    //glRotated(2, 0, 1, 0);
    glColor3f(0.2, 0.56, 0.);
    glutSolidCube(0.2); 
    
    glPopMatrix();
}  
