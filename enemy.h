#include "utils.h"

typedef struct enemy Enemy;
struct enemy {
    int life;           /*de 0 a 100*/
    Position position;  /*X, Y e Z  */
    int precision;       /*de 0 a 10 */
};

/*
Recebe uma posicao e precisao e retorna um ponteiro para
um novo inimigo com esses atributos
*/
int shouldShoot(Position shipP, Position enemyP);

/*
Recebe uma posicao e precisao e retorna um ponteiro para
um novo inimigo com esses atributos
*/
Enemy* createEnemy(Position myPosition, int precision);

/*
Recebe um ponteiro para um inimigo e desaloca-o da 
memoria
*/
int killEnemy(Enemy* en);

/*
Recebe um inteiro com o valor do damage recebido e um
ponteiro para um inimigo. Tira essa quantidade 
*/
void gotShot(Enemy* en, int damage);

/*
Recebe um ponteiro para um inimigo e retorna TRUE se estiver
vivo ou FALSE se tiver morto.
*/
int isAlive(Enemy* en);