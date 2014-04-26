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
Shot* createShot(Position shotP, Velocity shotV, int damage);

/*Recebe um ponteiro para um tiro e desaloca a memória 
 * alocada para ele.
 */
void freeShot(Shot* sh);

/*Módulo da velocidade do tiro*/
extern float shotNorm;

/*Recebe um ponteiro para um tiro e atualiza sua posição na tela.*/
void updateShot(Shot* sh);

/*Recebe (escalares) uma posição So, velocidade v e retorna a nova 
 * posição após o tempo de atualização da tela.
 */
float spaceTimeEquation(float initialPosition, float v);

/*Recebe o ponteiro para um tiro e calcula a norma de suas velocidades (x,y,z).
 */
float computeShotNorm(Shot* sh);
