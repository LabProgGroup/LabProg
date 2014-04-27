#include "utils.h"
#include "shot.h"

#define SHOOTABLE_DISTANCE 20 /*distancia minima para atirar na nave*/

typedef struct enemy Enemy;
struct enemy {
    int life;           /*de 0 a 100*/
    Position position;  /*X, Y e Z  */
    int precision;      /*de 0 a 10 */
};

/*
Recebe a posição da nave e decide se vai atirar ou não considerando
a distancia entre a nave e o inimigo
*/
int shouldShoot(Position shipP, Position enemyP);

/*
Recebe a posição da nave e a posição do inimigo que atirou, além da
"potência" do tiro. Além disso, retorna um ponteiro para o tiro.
*/
Shot* shootFromEnemy(Position enemyP, Position shipP, int power);

/*
Recebe uma posicao e precisao e retorna um ponteiro para um novo
inimigo com esses atributos
*/
Enemy* createEnemy(Position myPosition, int precision);

/*
Recebe um ponteiro para um inimigo e desaloca-o da memoria
*/
int killEnemy(Enemy* en);

/*
Recebe um inteiro com o valor do damage recebido e um ponteiro para 
um inimigo. Tira essa quantidade 
*/
void gotShotEnemy(Enemy* en, int damage);

/*
Recebe um ponteiro para um inimigo e retorna TRUE se estiver vivo ou
FALSE se tiver morto.
*/
int isEnemyAlive(Enemy* en);
