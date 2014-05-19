#include <stdio.h>
#include "cenario.h"
#include "queue.h"
#include "enemy.h"
#include "utils.h"
#include "ship.h"

void printCenario(Cenario *cenario) {
    printf("\nCenario:\n\tDimensions: %f %f %f", cenario->dimension.x, cenario->dimension.y, cenario->dimension.z);
    printf("\n\tEnemies: %p\n", (void *)cenario->enemies);
}

void printQueue(Queue *queue) {
    Node *node = queue->head->next;
    
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

void printShip(Ship *ship) {
    printf("\nShip:\n\tLife: %d", ship->life);
    printPosition(ship->position);
    printVelocity(ship->velocity);
    
}

void printShot(Shot *shot) {
    printf("\nShot:\n\tdamage: %d", shot->damage);
    printPosition(shot->shotPosition);
    printVelocity(shot->shotVelocity);
}

int main(int argc, const char * argv[])
{
    Cenario *cenario = createCenario(defaultCenarioDim);
    printCenario(cenario);
    printQueue(cenario->enemies);
    
    Position shipInitialPosition = {
        cenario->dimension.x / 2,
        cenario->dimension.y / 2,
        0
    };

    printPosition(shipInitialPosition);
    printQueue(cenario->enemies);
    
    Ship *ship = createShip(shipInitialPosition);
    printShip(ship);
    
    Key keyPressed = -1; /* Representa a tecla apertada */
    Position mousePosition;
    Shot *shipShot = NULL;
    int i;

    printf("def lalala: %f %f %f", defaultCenarioDim.x, defaultCenarioDim.y, defaultCenarioDim.z);
    for (i = 0; ; i = (i + 1) % MAX_LOOP) {
        if (i % 20 == 0) {
            if (keyPressed == CLICK) {
                scanf("%f %f %f", &mousePosition.x, &mousePosition.y, &mousePosition.z);
                shipShot = shootFromShip(mousePosition, ship->position, 20);
            }
            else
                updateVelocity(ship, keyPressed);

            updateShipPosition(ship);
            insideKeeper(ship, cenario->dimension);
            
            if (shipShot != NULL) {
                updateShot(shipShot);
                if (verifyShotColision(shipShot, cenario) == TRUE) {
                    freeShot(shipShot);
                    shipShot = NULL;
                }
            }
            if (verifyShipColision(ship, cenario) == TRUE) {
                killEnemy(dequeue(cenario->enemies));
                gotDamagedShip(ship, 50);
            }
            refreshCenario(cenario, ship->position);
            if (ship->life <= 0) {
                printf("\nGAME OVER\n");
                return 0;
            }
            
            if (shipShot != NULL)
                printShot(shipShot);
            
            printShip(ship);
            scanf("%d", &keyPressed);
        }     
    }  
    return 0;
}

