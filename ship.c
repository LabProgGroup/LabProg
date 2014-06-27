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

Shot* shootFromShip(Ship *sh, Position aimV, int power) {
    Shot* newShot;
    Velocity shotV;
    Position shotP = sh->position;
    shotV.x = aimV.x;
    shotV.y = aimV.y; 
    shotV.z = aimV.z;
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

Velocity getAimV(int x, int y, Ship* sh, int cenx, int ceny) {
    Velocity shotV;
    float xc = ((x*cenx) / glutGet(GLUT_WINDOW_WIDTH)) - cenx/2 + sh->position.x;
    float yc =  ceny/2 - (y*ceny) / glutGet(GLUT_WINDOW_HEIGHT) + sh->position.y;
    float zc = sqrt(SHIP_SHOT_NORM * SHIP_SHOT_NORM - (xc * xc + yc * yc));
    float z = zc + sh->velocity.z;
    float correction = z / (zc * 1.5);
    xc = xc * correction;
    yc = yc * correction;
    shotV.x =  xc * 1;
    shotV.y =  yc * 2;
    shotV.z = z;
    return shotV;
}

void renderAim(Ship* sh, Velocity v, int n) { 
    int i = 0;
    Position pos = sh->position;
    float dt = 10 / v.z;
    glPushMatrix();
    glLineWidth(2); 
    glColor4f(0, 1, 1, 0.5);

    // float newz = v.z + sh->velocity.z;
    // float correction = 

    //v.z = newz;

    glBegin(GL_LINES);
        glVertex3f(pos.x, pos.y, 0);
        glVertex3f(pos.x + v.x * 5000, pos.y + v.y * 5000, -v.z * 5000);
    glEnd();

    for (i = 1; i < 200; i++)
    {   
        //space time
        pos.x = pos.x + v.x * dt * i;
        pos.y = pos.y + v.y * dt * i - (GRAVITY * dt * dt * i * i) / 2;
        pos.z = pos.z + v.z * dt * i;
        //speed time
        v.x = v.x;
        v.y = v.y - GRAVITY * dt * i;
        v.z = v.z;
        glTranslatef(pos.x, pos.y,  -pos.z + shipPosition);
        glutWireCube(10);
    }
    glPopMatrix();
}