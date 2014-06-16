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
    randomPos.x = rand() % (2 * (int)cenario->dimension.x) - cenario->dimension.x;
    randomPos.y = rand() % (2 * (int)cenario->dimension.y) - cenario->dimension.y;
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

void renderParedes() {
    glColor4f(0.22, 0.22, 0.3, 0.3);
    /* Parede direita */
    GLfloat paredeColor[]  = {0.22, 0.22, 0.22};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, paredeColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  paredeColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  paredeColor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);
    

    int p1 = 90;
    glBegin(GL_QUADS);
    {
        glNormal3f(-1, 1, 0);
        glVertex3f(p1, 0, 0);
        glVertex3f(p1 / 2, -p1 / 2, 0);
        glVertex3f(p1 / 2, -p1 / 2, -5000);
        glVertex3f(p1, 0, -5000);
    }
    glEnd();

    /* Parede esquerda */
    glBegin(GL_QUADS);
    {
        glNormal3f(1, 1, 0);
        glVertex3f(-p1, 0, 0);
        glVertex3f(-p1 / 2, -p1 / 2, 0);
        glVertex3f(-p1 / 2, -p1 / 2, -5000);
        glVertex3f(-p1, 0, -5000);
    }
    glEnd();

    /* Rio */
    GLfloat rioColor[]  = {0.43, 0.73, 0.9};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, rioColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  rioColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  rioColor);
    glColor4f(0.43, 0.73, 0.9, 0.9);
    glBegin(GL_QUADS);
    {
        glNormal3f(0, 1, 0);
        glVertex3f(-p1 / 2, -p1 / 2, 0);
        glVertex3f(p1 / 2, -p1 / 2, 0);
        glVertex3f(p1 / 2, -p1 / 2, -5000);
        glVertex3f(-p1 / 2, -p1 / 2, -5000);
    }
    glEnd();
}

void renderBackground() {
    glEnable(GL_TEXTURE_2D);
    glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 30);
        glVertex3f(-9000, -9000, -4900);

        glTexCoord2f(30, 30);
        glVertex3f(9000, -9000, -4900);

        glTexCoord2f(30, 0);
        glVertex3f(9000, 9000, -4900);

        glTexCoord2f(0, 0);
        glVertex3f(-9000, 9000, -4900);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void renderCenario(Cenario* cen) {
    renderBackground();
    renderParedes();
    renderEnemyQ(cen->enemies);
}
