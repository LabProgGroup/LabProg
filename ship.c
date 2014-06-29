#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "utils.h"
#include "ship.h"

static BOOL isOnfocus;

Ship* createShip(Position position, float myradius) {
    Ship* newship = malloc(sizeof (Ship));
    newship->life = 100;
    newship->focus = 300;
    newship->score = 0;
    isOnfocus = FALSE;

    newship->position.x = position.x;
    newship->position.y = position.y;
    newship->position.z = position.z;

    newship->velocity.x = 0;
    newship->velocity.y = 0;
    newship->velocity.z = INITIAL_VELOCITY;
    
    newship->radius = myradius;
    return newship;
}

void killShip(Ship* sh) {
    free(sh);
}

void updateVelocity(Ship *sh, unsigned char key) {
    switch (key) {
        case 'w':
            if (sh->velocity.y < 0) sh->velocity.y = 0;
            sh->velocity.y += MOVING_FACTOR;
            break;
        case 's':
            if (sh->velocity.y > 0) sh->velocity.y = 0;
            sh->velocity.y -= MOVING_FACTOR;
            break;
        case 'd':
            if (sh->velocity.x < 0) sh->velocity.x = 0;
            sh->velocity.x += MOVING_FACTOR;
            break;
        case 'a':
            if (sh->velocity.x > 0) sh->velocity.x = 0;
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
            if (sh->focus > 20) {
                clockTick = 1.0 / 500;
                isOnfocus = TRUE;
            }
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
            isOnfocus = FALSE;
            break;
    }
}

void updateShipPosition(Ship* sh) {
    sh->position = spaceTimeEquation(sh->position, sh->velocity);
}

void updateScore(Ship* sh) {
    sh->score++;
}

void updateFocus(Ship* sh) {
    if (isOnfocus && sh->focus > 0)
        sh->focus--;
    if (!isOnfocus &&  sh->focus < 300)
        sh->focus++;
    if (isOnfocus && sh->focus == 0)
        clockTick = (float)1 / 50;
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
    if (sh->life < 0)
        gameState = GAME_OVER;
}

BOOL isShipAlive(Ship* sh) {
    return sh->life > 0;
}

void renderShip(Ship* sh) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(sh->position.x - 2, sh->position.y - 5, -sh->position.z + shipPosition);
    glRotatef(206, 0.0f, 1.0f, 0.0f);
    glColor4f(0.255, 0.256, 0.208, 1);
    glScalef(1.5, 1.5, 1.5);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, idShipBase);
    #include "shipBase.inc"
    glColor4f(1., 1., 1., 1);
    glBindTexture(GL_TEXTURE_2D, idShipCream);
    #include "shipCream.inc"
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(sh->position.x, sh->position.y, -sh->position.z + shipPosition);
    glColor4f(0, 1, 0, 0.3);
    glutSolidSphere(sh->radius, 30, 30);　// tirar depois

    glPopMatrix();
}

Velocity getAimV(int x, int y, Ship* sh, int cenx, int ceny) {
    Velocity shotV;
    float xc = ((x*cenx) / glutGet(GLUT_WINDOW_WIDTH)) - cenx/2 + sh->position.x;
    float yc =  ceny/2 - (y*ceny) / glutGet(GLUT_WINDOW_HEIGHT) + sh->position.y;
    float zc = sqrt(SHIP_SHOT_NORM * SHIP_SHOT_NORM - (xc * xc + yc * yc));
    float z = zc + sh->velocity.z;
    float correction = z / zc;
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
    float dt = 50 / v.z;

    glPushMatrix();
    glLineWidth(2); 
    glColor4f(0, 1, 1, 0.5);
    for (i = 3; i < n + 3; i++)
    {   
        //space time
        pos.x = pos.x + v.x * dt * i;
        pos.y = pos.y + v.y * dt * i - (GRAVITY * dt * dt * i * i) / 2;
        pos.z = pos.z + v.z * dt * i;
        //speed time
        v.x = v.x;
        v.y = v.y - GRAVITY * dt * i;
        v.z = v.z;
        glPushMatrix();
            glTranslatef(pos.x, pos.y,   - pos.z + shipPosition);
            glutWireCube(10);
        glPopMatrix();
    }
    glPopMatrix();
}
