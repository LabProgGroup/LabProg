#include "cenario.h"
#include "enemy.h"
#include "enemyQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Cenario* createCenario(Dimension dimension) {
    Cenario *cen = malloc (sizeof(Cenario));
    
    cen->enemies = createEnemyQueue();

    cen->dimension.x = dimension.x;
    cen->dimension.y = dimension.y;
    cen->dimension.z = dimension.z;
    initEnemies(cen);

    srand((unsigned int)time(NULL));
    
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
        free (dequeueEnemy(cenario->enemies));
        firstEnemy = cenario->enemies->first;
    }
}

static void createNewEnemyInInterval(float min, float max, Cenario *cenario){
    int precision = rand();
    
    Position randomPos;
    randomPos.x = rand() % (int)cenario->dimension.x;
    randomPos.y = 0;
    randomPos.z = rand() % (int)(max - min) + min;
    
    enqueueEnemy(createEnemy(randomPos, defaultEnemyDim, precision), cenario->enemies);
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

BOOL verifyShipColision(Ship *ship, Cenario *cenario) {
    Enemy *first = cenario->enemies->first;
    if (ship->position.x >= first->position.x &&
        ship->position.x <= first->position.x + first->dimension.x)
        if (ship->position.z >= first->position.z)
            return TRUE;
    return FALSE;
}

BOOL verifyShotColision(Shot *shot, Cenario *cenario) {
    if (isInsideCenario(shot->position, cenario))
        return TRUE;
    
    else {
        EnemyNode *node = cenario->enemies->head->next;
        while (node != cenario->enemies->head) {
            if (shot->position.x == node->enemy->position.x)
                if (shot->position.z >= node->enemy->position.z) {
                    gotShotEnemy(node->enemy, 20);
                    if (node->enemy->life <= 0)
                        removeEnemyNode(node, cenario->enemies);
                    return TRUE;
                }
            node = node->next;
        }
    }
    
    return FALSE;
}

BOOL isInsideCenario(Position position, Cenario *cenario) {
    if (position.x <= 0 || position.x >= cenario->dimension.x ||
        position.y <= 0 || position.y >= cenario->dimension.y ||
        position.z <= 0 || position.z >= cenario->dimension.z)
        return TRUE;
    return FALSE;
}


