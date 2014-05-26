#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "utils.h"
#include "shot.h"

#define ENEMY_SHOT_VELOCITY 60
#define SHOOTABLE_DISTANCE 20 

typedef struct {
    int life;         
    Position position;
    int precision;   

    Dimension dimension;
} Enemy;

Enemy* createEnemy(Position myPosition, Dimension myDimension, int precision);
void killEnemy(Enemy* en);

Shot* shootFromEnemy(Position enemyP, Position shipP, int power);
BOOL shouldShoot(Position shipP, Position enemyP);
void gotShotEnemy(Enemy* en, int damage);
BOOL isEnemyAlive(Enemy* en);

#endif
