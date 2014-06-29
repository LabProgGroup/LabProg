#include "cenario.h"
#include "enemy.h"
#include "enemyQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void createNewEnemyInInterval(float min, float max, Cenario *cenario) {
    Position randomPos;
    randomPos.x = (rand() % (2 * (int)cenario->dimension.x)) - cenario->dimension.x;
    randomPos.y = (rand() % (2 * (int)cenario->dimension.y)) - cenario->dimension.y;
    randomPos.z = rand() % (int)(max - min) + min;
    
    enqueueEnemy(createEnemy(randomPos, 10), cenario->enemies);
}

void initEnemies(Cenario *cenario) {
    Enemy *lastEnemy;
    
    createNewEnemyInInterval(0, MAX_DISTANCE_BETWEEN_ENEMIES, cenario);
    lastEnemy = cenario->enemies->last;
    
    while (BUFFER_SIZE - lastEnemy->position.z > MAX_DISTANCE_BETWEEN_ENEMIES) {
        createNewEnemyInInterval(lastEnemy->position.z, lastEnemy->position.z + MAX_DISTANCE_BETWEEN_ENEMIES, cenario);
        lastEnemy = cenario->enemies->last;
    }
}

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

BOOL verifyShipColision(Ship *ship, Cenario *cenario) {
    EnemyNode *node = cenario->enemies->head->next;

    while (node != cenario->enemies->head) {
        if (distance(ship->position, node->enemy->position) < ship->radius + node->enemy->radius)
            return TRUE;
        node = node->next;
    }
    return FALSE;
}

BOOL verifyEnemiesShotColision(Cenario *cenario, ShotQueue *shotQueue) {
    EnemyNode *eNode = cenario->enemies->head->next;
    ShotNode *shotNode = shotQueue->head->next;
    
    BOOL killedEnemy = FALSE; 
    while (eNode != cenario->enemies->head) {
        while (shotNode != shotQueue->head) {
            if (distance(shotNode->shot->position, eNode->enemy->position) < eNode->enemy->radius) {
                gotShotEnemy(eNode->enemy, shotNode->shot->damage); 
            }
            if (!isEnemyAlive(eNode->enemy)) {
                EnemyNode *kill = eNode;
                eNode = eNode->next;
                killedEnemy = TRUE;
                removeEnemyNode(kill, cenario->enemies);
            }
            shotNode = shotNode->next;
        }
        shotNode = shotQueue->head->next;
        if (!killedEnemy) eNode = eNode->next;
        else killedEnemy = FALSE;
    }
     
    return FALSE;
}

void rmFarShots(ShotQueue *shotQ, Cenario *cenario) {
    if (!isShotQueueEmpty(shotQ)) {
        ShotNode *stNode = shotQ->head->next;
        while (stNode != shotQ->head) {
            if (stNode->shot->position.z - shipPosition > 1000) {
                removeShotNode(stNode, shotQ);
            }
            stNode = stNode->next;
        }
    }
}

void renderBackground() {
    glEnable(GL_TEXTURE_2D);
    glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 1);
        glVertex3f(-9000, -9000, -5000);

        glTexCoord2f(1, 1);
        glVertex3f(9000, -9000, -5000);

        glTexCoord2f(1, 0);
        glVertex3f(9000, 9000, -5000);

        glTexCoord2f(0, 0);
        glVertex3f(-9000, 9000, -5000);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void renderCenario(Cenario* cen) {
    renderBackground();
    renderEnemyQ(cen->enemies);
}
