/**/
/*TODO: pensar gravidade.*/
#include "utils.h"
typedef struct shot {
    
    Position shotPosition;
    Velocity shotVelocity;
    int damage;

} Shot;



/*Recebe uma struct contendo as posições espaciais (x,y,z)
 * e as velocidades desses eixos (x,y,z) e retorna um ponteiro para
 * um tiro.
 */
Shot* createShot(Position shotP, Position shotV, int damage);

/*Recebe um ponteiro para um tiro e desaloca a memória 
 * alocada para ele.
 */
void freeShot(Shot* sh);
