#include "cenario.h"
#include "enemy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Cenario* createCenario(float x, float y, float z) {
    Cenario *cen = malloc (sizeof(Cenario));
    
    cen->enemies = createQueue();
    cen->dimension.x = x;
    cen->dimension.y = y;
    cen->dimension.z = z;
    
    xSize = x;
    ySize = y;
    
    srand((unsigned int)time(NULL));
    initEnemies(cen);
    
    return cen;
}

void refreshCenario(Cenario *cenario, Position shipPosition) {
    Enemy *firstEnemy = cenario->enemies->first;
    Enemy *lastEnemy = cenario->enemies->last;
    float max = BUFFER_SIZE + shipPosition.z;
    
    while (max - lastEnemy->position.z > MAX_DISTANCE_BETWEEN_ENEMIES) {
        createNewEnemyInInterval(lastEnemy->position.z, max, cenario);
        lastEnemy = cenario->enemies->last;
    }
    while (shipPosition.z > firstEnemy->position.z) {
        free (dequeue(cenario->enemies));
        firstEnemy = cenario->enemies->first;
    }
    
}

static void createNewEnemyInInterval(float min, float max, Cenario *cenario){
    int precision = rand();
    
    Position randomPos;
    randomPos.x = rand() % (int)cenario->dimension.x;
    randomPos.y = 0;
    randomPos.z = rand() % (int)(max - min) + min;
    
    enqueue (createEnemy(randomPos, precision), cenario->enemies);
}

static void initEnemies(Cenario *cenario) {
    Enemy *lastEnemy;
    
    createNewEnemyInInterval(0, MAX_DISTANCE_BETWEEN_ENEMIES, cenario);
    lastEnemy = cenario->enemies->last;
    
    while (BUFFER_SIZE - lastEnemy->position.z > MAX_DISTANCE_BETWEEN_ENEMIES) {
        createNewEnemyInInterval(lastEnemy->position.z, lastEnemy->position.z + MAX_DISTANCE_BETWEEN_ENEMIES, cenario);
        lastEnemy = cenario->enemies->last;
    }
    
}

int verifyShipColision(Ship *ship, Cenario *cenario) {
    if (ship->position.x == cenario->enemies->first->position.x)
        if (ship->position.z >= cenario->enemies->first->position.z)
            return TRUE;
    return FALSE;
}

int verifyShotColision(Shot *shot, Cenario *cenario) {
    if (shot->shotPosition.x <= 0 || shot->shotPosition.x >= xSize ||
        shot->shotPosition.y <= 0 || shot->shotPosition.y >= ySize ||
        shot->shotPosition.z >= cenario->dimension.z)
        return TRUE;
    
    else {
        Node *node = cenario->enemies->head->next;
        while (node != cenario->enemies->head) {
            if (shot->shotPosition.x == node->enemy->position.x)
                if (shot->shotPosition.z >= node->enemy->position.z) {
                    gotShotEnemy(node->enemy, 20);
                    if (node->enemy->life <= 0)
                        removeNode(node, cenario->enemies);
                    return TRUE;
                }
            node = node->next;
        }
    }
    
    return FALSE;
}



