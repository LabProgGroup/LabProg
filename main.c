#include <stdio.h>
#include "cenario.h"
#include "enemyQueue.h"
#include "enemy.h"
#include "utils.h"
#include "ship.h"
#include "shotQueue.h"

void printCenario(Cenario *cenario) {
    printf("\nCenario:\n\tDimensions: %f %f %f", cenario->dimension.x, cenario->dimension.y, cenario->dimension.z);
    printf("\n\tEnemies: %p\n", (void *)cenario->enemies);
}

void printEnemyQueue(EnemyQueue *queue) {
    EnemyNode *node = queue->head->next;
    
    printf("\nQueue:\n\tHead: %p %p %p", (void *)queue->head, (void *)queue->head->enemy, queue->head->next);
    printf("\n\tlastNode: %p", (void *)queue->lastNode);
    printf("\n\tfirst: %p last: %p", (void *)queue->first, (void *)queue->last);
    
    while (node != queue->head) {
        printf("\n\tNode: %p %p %p z: %f x: %f", (void *)node, (void *)node->enemy, (void *)node->next, node->enemy->position.z, node->enemy->position.x);
        node = node->next;
    }
    printf("\n");
}

void printPosition(Position position) {
    printf("\nPosition:\n\tx: %f\n\ty: %f\n\tz: %f\n", position.x, position.y, position.z);
}

void printVelocity(Position position) {
    printf("\nVelocity:\n\tx: %f\n\ty: %f\n\tz: %f\n", position.x, position.y, position.z);
}

void printEnemy(Enemy *enemy) {
    printf("\nEnemy:\n\t%p\n\tlife: %d\n\tprecision: %d", enemy, enemy->life, enemy->precision);
    printPosition(enemy->position);
}

void printScore(Ship *ship) {
    printf("\nScore: %.2f\n", traveledDistance);
}

void printShip(Ship *ship) {
    printf("\nShip:\n\tLife: %d", ship->life);
    printPosition(ship->position);
    printVelocity(ship->velocity);
    printScore(ship);
}

void printShot(Shot *shot) {
    printf("\nShot:\n\tdamage: %d", shot->damage);
    printPosition(shot->shotPosition);
    printVelocity(shot->shotVelocity);
}

Key readKey() {
    Key keyPressed;
    scanf("%d", &keyPressed);
    return keyPressed;
}

int main(int argc, const char * argv[]) {
    Cenario *cenario = createCenario(defaultCenarioDim);
    printCenario(cenario);
    printEnemyQueue(cenario->enemies);
    
    Position shipInitialPosition = {
        cenario->dimension.x / 2,
        cenario->dimension.y / 2,
        0
    };

    printPosition(shipInitialPosition);
    printEnemyQueue(cenario->enemies);
    
    Ship *ship = createShip(shipInitialPosition);
    printShip(ship);
    
    Key keyPressed = -1; /* Representa a tecla apertada */
    Position mousePosition;
    ShotQueue *shipShotsQueue = createShotQueue();

    int i;
    for (i = 0; ; i = (i + 1) % MAX_LOOP) {
        if (i % 20 == 0) {
            keyPressed = readKey();
            if (keyPressed == CLICK) {
                scanf("%f %f %f", &mousePosition.x, &mousePosition.y, &mousePosition.z);
                enqueueShot(shootFromShip(mousePosition, ship->position, 20), shipShotsQueue);
            }
            else
                updateVelocity(ship, keyPressed);

            updateShipPosition(ship);
            updateScore(ship);
            insideKeeper(ship, cenario->dimension);
            
            /* Achei isso feio */
            if (!isShotQueueEmpty(shipShotsQueue)) {
                ShotNode *stNode = shipShotsQueue->head->next;
                while (stNode != shipShotsQueue->head) {
                    updateShot(stNode->shot);
                    if (verifyShotColision(stNode->shot, cenario) == TRUE) {
                        ShotNode *aux = stNode->next;
                        removeShotNode(stNode, shipShotsQueue);
                        stNode = aux;
                    }
                    else
                        stNode = stNode->next;
                }
            }

            if (verifyShipColision(ship, cenario) == TRUE) {
                killEnemy(dequeueEnemy(cenario->enemies));
                gotDamagedShip(ship, 50);
            }
            refreshCenario(cenario, ship->position);
            if (ship->life <= 0) {
                printf("\nGAME OVER\n");
                return 0;
            }
            
            if (!isShotQueueEmpty(shipShotsQueue)) {
                Shot *st;
                printf("\nShipShots:\n");
                int a = 0;
                foreach(st, shipShotsQueue)
                   printf("\t%p\n", st);
            }
                        
            printShip(ship);
        }     
    }  
    return 0;
}

