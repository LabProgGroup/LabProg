#include "utils.h"
#include "shot.h"

typedef struct ship Ship;
struct ship {
    int life;           /*de 0 a 100*/
    Position position;  /*X, Y e Z  */
    Velocity velocity;	/*Em m/s sem valor definido por enquanto :/ */
};

#define INITIAL_VELOCITY 60
/*
Recebe uma posição(mira), a posição da nave e um inteiro com a "potencia"
do tiro
*/
Shot* shootFromShip(Position aimP, Position shipP, int power);

/*
Retorna um ponteiro para uma nova nave
*/
Ship* createShip();

/*
Recebe um ponteiro para a nave e desaloca-a da memoria
*/
int killShip(Ship* sh);

/*
Recebe um inteiro com o valor do damage recebido e um ponteiro para a
nave. Tira essa quantidade de damage da vida da nave 
*/
void gotShotShip(Ship* sh, int damage);

/*
Recebe um ponteiro para a nave e retorna TRUE se estiver viva ou
FALSE se tiver destruida.
*/
int isShipAlive(Ship* sh);