#include <stdio.h>
#include "shot.h"
#include "utils.h"
/*Módulo da velocidade do tiro*/
float shotNorm;

/*Recebe uma struct contendo as posições espaciais (x,y,z)
 * e as velocidades desses eixos (x,y,z) e retorna um ponteiro para
 * um tiro.
 */
Shot* createShot(Position shotP, Velocity shotV, int damage) {
    Shot *sh = (Shot*) malloc(sizeof (Shot));
    sh->shotPosition = shotP;
    sh->shotVelocity = shotV;
    sh->damage = damage; 
    return sh;
} 
/*Recebe um ponteiro para um tiro e desaloca a memória 
 * alocada para ele.
 */
void freeShot(Shot* sh) {
    if (sh != NULL)
        free(sh);
}
/*Recebe um ponteiro para um tiro e atualiza sua posição na tela.*/
void updateShot(Shot* sh) {
    sh->shotPosition.x = spaceTimeEquation(sh->shotPosition.x, sh->shotVelocity.x);
    sh->shotPosition.y = spaceTimeEquation(sh->shotPosition.y, sh->shotVelocity.y);
    sh->shotPosition.z = spaceTimeEquation(sh->shotPosition.z, sh->shotVelocity.z);
    computeShotNorm(sh);
}

/*Recebe o ponteiro para um tiro e calcula a norma de suas velocidades (x,y,z).
 */
float computeShotNorm(Shot* sh) {
    shotNorm = sqrt(sh->shotVelocity.x*sh->shotVelocity.x + sh->shotVelocity.y*sh->shotVelocity.y + sh->shotVelocity.z*sh->shotVelocity.z); 
    return shotNorm;
}






