#ifndef _SHIP_H_
#define _SHIP_H_

#include "shot.h"

typedef struct ship Ship;
struct ship {
    int life;           /*de 0 a 100*/
    Position position;  /*X, Y e Z  */
    Velocity velocity;	/*Em m/s sem valor definido por enquanto :/ */
};

#define INITIAL_VELOCITY 10 /*Velocidade inicial da nave*/
#define MOVING_FACTOR 2     /*O quanto a nave vira quando ela muda de orientação*/
#define VELOCITY_FACTOR 10
#define MAX_XY_ORIENTATION 15
#define MAX_VELOCITY 100
/*
 Retorna um ponteiro para uma nova nave
 */
Ship* createShip();

/*
Recebe uma posição(mira), a posição da nave e um inteiro com a "potencia"
do tiro
*/
Shot* shootFromShip(Position aimP, Position shipP, int power);

/*
Recebe um ponteiro para a nave e um inteiro que se 1 move a nave para
a direita e se for -1 move a nave para a esquerda
*/
void moveShipHorizontally(Ship* sh, int direction);

/*
Recebe um ponteiro para a nave e um inteiro que se 1 move a nave para
a direita e se for -1 move a nave para a esquerda
*/
void moveShipVetically(Ship* sh, int direction);

/*
Recebe um ponteiro para a nave e um inteiro que se 1 aumenta a
velocidade da nave e se for -1 diminui a velocidade da nave
*/
void changeShipSpeed(Ship* sh, int direction);

/*
Recebe um ponteiro para a nave e atualiza a sua posição de acordo
com o tick do relogio
*/
void updateShipPosition(Ship* sh);

/*
Recebe um ponteiro para a nave e desaloca-a da memoria
*/
int killShip(Ship* sh);

/*
Recebe um inteiro com o valor do damage recebido e um ponteiro para a
nave. Tira essa quantidade de damage da vida da nave 
*/
void gotDamagedShip(Ship* sh, int damage);

/*
Recebe um ponteiro para a nave e retorna TRUE se estiver viva ou
FALSE se tiver destruida.
*/
int isShipAlive(Ship* sh);

/* Não deixa a nave sair do espaço do cenario */
void insideKeeper(Ship *sh);

#endif