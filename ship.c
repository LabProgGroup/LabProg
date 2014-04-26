#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

#include "ship.h"

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

/*
Retorna um ponteiro para uma nova nave
*/
Ship* createShip() {
    Ship* newship = malloc(sizeof (Ship));
    newship->life = 100;
    newship->position.x = xSize / 2;
    newship->position.y = ySize / 2;
    newship->position.z = 0;
    newship->velocity.x = 0;
    newship->velocity.y = 0;
    newship->velocity.z = INITIAL_VELOCITY;
}

/*
Recebe um ponteiro para a nave e desaloca-a da memoria
*/
int killShip(Ship* sh) {
    free(sh);
    return 1;
}

/*
Recebe um inteiro com o valor do damage recebido e um ponteiro para a
nave. Tira essa quantidade de damage da vida da nave 
*/
void gotShotShip(Ship* sh, int damage) {
    sh->life -= damage;
}

/*
Recebe um ponteiro para a nave e retorna TRUE se estiver viva ou
FALSE se tiver destruida.
*/
int isShipAlive(Ship* sh) {
    return sh->life > 0;
}