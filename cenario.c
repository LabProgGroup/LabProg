#include "cenario.h"
#include "enemy.h"
#include <stdio.h>
#include <stdlib.h>

Cenario* createCenario() {
    Cenario *cen = malloc (sizeof(Cenario));
    
    cen->enemies = createQueue();
    cen->dimension.x = 0;
    cen->dimension.y = 0;
    cen->dimension.z = 0;
    
    return cen;
}

void updateCenario(Cenario *cenario, Position shipPosition) {
    if (cenario->enemies->last->position.z <
        shipPosition.z + (NUMBER_OF_ENEMIES - 1) * BUFFER_SIZE)
        createNewEnemy(cenario);
    
    
}

static void createNewEnemy(Cenario *cenario) {
    int precision; /* ??? */
    Enemy *lastEnemy = cenario->enemies->last;
    
    srand((int)lastEnemy->position.x + lastEnemy->position.y + lastEnemy->position.z);
    
    Position randomPos;
    randomPos.x = rand() % (int)cenario->dimension.x;
    randomPos.y = 0;
    randomPos.z = rand() % (BUFFER_SIZE - (int)lastEnemy->position.z) + lastEnemy->position.z;
    
    enqueue (createEnemy(randomPos, precision), cenario->enemies);
}