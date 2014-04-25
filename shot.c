#include <stdio.h>
#include "shot.h"
#include "utils.h"
/*Recebe uma struct contendo as posições espaciais (x,y,z)
 * e as velocidades desses eixos (x,y,z) e retorna um ponteiro para
 * um tiro.
 */
Shot* createShot(Position shotP, Position shotV, int damage) {
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
