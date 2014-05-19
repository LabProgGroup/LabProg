#ifndef _SHOT_H_
#define _SHOT_H_
/*TODO: pensar gravidade.*/
#include "utils.h"

typedef struct {
    Position shotPosition;
    Velocity shotVelocity;
    int damage;
} Shot;

#define SHOOT_NORM 60

/*Recebe uma struct contendo as posições espaciais (x,y,z)
 * e as velocidades desses eixos (x,y,z) e retorna um ponteiro para
 * um tiro.
 */
Shot* createShot(Position shotP, Velocity shotV, int damage);

/*Recebe um ponteiro para um tiro e desaloca a memória 
 * alocada para ele.
 */
void freeShot(Shot* sh);

/*Módulo da velocidade do tiro*/
extern float shotNorm;

/*Recebe um ponteiro para um tiro e atualiza sua posição na tela.*/
void updateShot(Shot* sh);

/*Recebe o ponteiro para um tiro e calcula a norma de suas velocidades (x,y,z).
 */
float computeShotNorm(Shot* sh);
#endif
