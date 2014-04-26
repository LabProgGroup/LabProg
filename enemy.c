#include <stdlib.h>  
#include <stdio.h>   
#include <math.h>

#include "enemy.h"

/*
Recebe a posição da nave e decide se vai atirar ou não considerando
a distancia entre a nave e o inimigo
*/
int shouldShoot(Position shipP, Position enemyP) {
    if (distance(shipP, enemyP) < SHOOTABLE_DISTANCE)
        return TRUE;
    return FALSE;
}

/*
Recebe a posição da nave e a posição do inimigo que atirou, além da
"potência" do tiro. Além disso, retorna um ponteiro para o tiro.
*/
Shot* shootFromEnemy(Position enemyP, Position shipP, int power) {
    Shot* newShot;
    Position shotP = enemyP;
    /*Definindo o vetor velocidade do tiro:*/
    Velocity shotV;
    shotV.x = shipP.x - enemyP.x;
    shotV.y = shipP.y - enemyP.y;
    shotV.z = -1 * sqrt(SHOOT_NORM * SHOOT_NORM - shotV.x * shotV.x - shotV.y * shotV.y); 
    newShot = createShot(shotP, shotV, power);
    return newShot;
}

/*
Recebe uma posicao e precisao e retorna um ponteiro para
um novo inimigo com esses atributos
*/
Enemy* createEnemy(Position myPosition, int precision) {
    Enemy *newEnemy = malloc(sizeof (Enemy));
    newEnemy->life = 100;
    newEnemy->position = myPosition;
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
void gotShotEnemy(Enemy* en, int damage) {
    en->life -= damage;
}

/*
Recebe um ponteiro para um inimigo e retorna TRUE se estiver
vivo ou FALSE se tiver morto.
*/
int isEnemyAlive(Enemy* en) {
    return en->life > 0;
}

int isEnemyAtScreen(Position shipP, Position enemyP) {
    return shipP.z <= enemyP.z;
}