#include <stdlib.h>  /* NULL, free() */
#include <stdio.h>   /* printf(), scanf()*/

#include "enemy.h"
#include "utils.h"

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
    return newEnemy;
}

/*
Recebe um ponteiro para um inimigo e desaloca-o da 
memoria
*/
int killEnemy(Enemy* dead) {
    free(dead);
    return 1;
}

/*
Recebe um inteiro com o valor do damage recebido e um
ponteiro para um inimigo. Tira essa quantidade 
*/
void gotShot(Enemy* en, int damage) {
    en->life -= damage;
}

/*
Recebe um ponteiro para um inimigo e retorna TRUE se estiver
vivo ou FALSE se tiver morto.
*/
int isAlive(Enemy* en) {
    if (en->life <= 0)
        return FALSE;
    else
        return TRUE;
}