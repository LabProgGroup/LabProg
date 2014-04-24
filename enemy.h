#include "utils.h"

typedef struct enemy Enemy;
struct enemy {
    int life;           /*de 0 a 100*/
    Position position;  /*X, Y E Z  */
    int precision;       /*de 0 a 10 */
};

int shouldShoot(Position shipP, Position enemyP);

Enemy* createEnemy(Position myPosition, int precision);

int killEnemy(Enemy* dead);