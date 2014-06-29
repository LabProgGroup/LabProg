#include <stdlib.h>  
#include <stdio.h>   
#include <math.h>

#include "enemy.h"

Enemy* createEnemy(Position myPosition, float myRadius) {
    Enemy *newEnemy = malloc(sizeof (Enemy));
    newEnemy->life = 100;
    newEnemy->position = myPosition;
    newEnemy->radius = myRadius;

    return newEnemy;
}

void killEnemy(Enemy* dead) {
    free(dead);
}

Shot* shootFromEnemy(Enemy* enemy, Ship* ship, int power) {
    Shot* newShot;
    Position shotP = enemy->position;
    Velocity shotV;

    float gama = distance(ship->position, enemy->position) * GRAVITY / (2 * ENEMY_SHOT_VELOCITY);

    shotV.x = ship->position.x - enemy->position.x;
    shotV.y = ship->position.y - enemy->position.y + gama;
    shotV.z = ship->position.z - enemy->position.z;

    float alpha = sqrt((shotV.x * shotV.x + shotV.y * shotV.y + shotV.z * shotV.z) / (ENEMY_SHOT_VELOCITY * ENEMY_SHOT_VELOCITY));

    shotV.x /= alpha;
    shotV.y /= alpha;
    shotV.z = shotV.z / alpha + ship->velocity.z;

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

void renderEnemy(Enemy* enemy) {
    Position p = enemy->position;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(p.x, p.y, -p.z + shipPosition);
    glColor4f(0.5, 0.35, 0.05, 0.9);
    #include "enemy.inc"
    glPopMatrix();
}
