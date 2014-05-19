#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

#include "ship.h"

/*
 Retorna um ponteiro para uma nova nave
 */
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

/*
Recebe uma posição(mira), a posição da nave e um inteiro com a "potencia"
do tiro e devolve um ponteiro para um novo tiro partindo da tela
*/
Shot* shootFromShip(Position aimP, Position shipP, int power) {
    Shot* newShot;
    Position shotP = shipP;
    /*Definindo o vetor velocidade do tiro:*/
    Velocity shotV;
    shotV.x = aimP.x - shipP.x;
    shotV.y = aimP.y - shipP.y;
    shotV.z = sqrt(SHOOT_NORM * SHOOT_NORM - shotV.x * shotV.x - shotV.y * shotV.y); 
    newShot = createShot(shotP, shotV, power);
    return newShot;
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

/*
Recebe um ponteiro para a nave e um inteiro que, se 1 aumenta a
velocidade da nave, se for -1 diminui a velocidade da nave
*/
void changeShipSpeed(Ship* sh, int direction) {
    if (sh->velocity.z + (direction * VELOCITY_FACTOR) >= MAX_VELOCITY)
        return;
    sh->velocity.z += (direction * VELOCITY_FACTOR);
}

/*
Recebe um ponteiro para a nave e atualiza a sua posição de acordo
com o tick do relogio
*/
void updateShipPosition(Ship* sh) {
    sh->position = spaceTimeEquation(sh->position, sh->velocity);
}

/*
Recebe um ponteiro para a nave e desaloca-a da memoria
*/
void killShip(Ship* sh) {
    free(sh);
}

/*
Recebe um inteiro com o valor do damage recebido e um ponteiro para a
nave. Tira essa quantidade de damage da vida da nave 
*/
void gotDamagedShip(Ship* sh, int damage) {
    sh->life -= damage;
}

/*
Recebe um ponteiro para a nave e retorna TRUE se estiver viva ou
FALSE se tiver destruida.
*/
BOOL isShipAlive(Ship* sh) {
    return sh->life > 0;
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