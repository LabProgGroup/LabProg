#include <stdlib.h>  /* NULL, free() */
#include <stdio.h>   /* printf(), scanf()*/

#include "enemy.h"

/*
Recebe uma posicao e precisao e retorna um ponteiro para
um novo inimigo com esses atributos
*/
int shouldShoot(Position shipP, Position enemyP) {
    if (distance(shipP, enemyP) < 20)
        return TRUE;
    return FALSE;
}

/*
Recebe uma posicao e precisao e retorna um ponteiro para
um novo inimigo com esses atributos
*/
Enemy* createEnemy(Position myPosition, int precision) {
    Enemy *newEnemy = malloc(sizeof (Enemy));
    newEnemy->life = 100;
    newEnemy->position.x = myPosition.x;
    newEnemy->position.y = myPosition.y;
    newEnemy->position.z = myPosition.z;
    newEnemy->precision = precision;
}

/*
Recebe um ponteiro para um inimigo e desaloca-o da 
memoria
*/
int killEnemy(Enemy* dead) {
    free(dead);
    return 1;
}