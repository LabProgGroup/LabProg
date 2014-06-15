#include <stdlib.h>  
#include <stdio.h>   
#include <math.h>

#include "enemy.h"

Enemy* createEnemy(Position myPosition, Dimension myDimension, int precision) {
    Enemy *newEnemy = malloc(sizeof (Enemy));
    newEnemy->life = 100;
    newEnemy->position = myPosition;
    newEnemy->dimension = myDimension;
    newEnemy->precision = precision;

    return newEnemy;
}

void killEnemy(Enemy* dead) {
    free(dead);
}

Shot* shootFromEnemy(Position enemyP, Position shipP, int power) {
    Shot* newShot;
    Position shotP = enemyP;
    Velocity shotV;
    shotV.x = shipP.x - enemyP.x;
    shotV.y = shipP.y - enemyP.y;
    shotV.z = -1 * sqrt(ENEMY_SHOT_VELOCITY * ENEMY_SHOT_VELOCITY - shotV.x * shotV.x - shotV.y * shotV.y); 
    newShot = createShot(shotP, shotV, power);
    return newShot;
}

BOOL shouldShoot(Position shipP, Position enemyP) {
    if (distance(shipP, enemyP) < SHOOTABLE_DISTANCE)
        return TRUE;
    return FALSE;
}

void gotShotEnemy(Enemy* en, int damage) {
    en->life -= damage;
}

BOOL isEnemyAlive(Enemy* en) {
    return en->life > 0;
}

Position sortEnemyPosition(float shipZ) {
    Position pos;
    return pos;
}