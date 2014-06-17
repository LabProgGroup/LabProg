#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "utils.h"
#include "shot.h"
#include "configuration.h"
#include "ship.h"


typedef struct {
    int life;         
    Position position;
    int precision;   

    float radius;
} Enemy;

Enemy* createEnemy(Position myPosition, float myRadius, int precision);
void killEnemy(Enemy* en);

Shot* shootFromEnemy(Enemy* enemy, Ship* ship, int power);
BOOL shouldShoot(Position shipP, Position enemyP);
void gotShotEnemy(Enemy* en, int damage);
BOOL isEnemyAlive(Enemy* en);
void renderEnemies();

#endif
