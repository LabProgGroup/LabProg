#include <stdio.h>
#include "cenario.h"
#include "queue.h"
#include "enemy.h"
#include "utils.h"
#include "ship.h"
#include "shot.h"

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
    Cenario *cenario = createCenario(20, 20, 2000);
    printCenario(cenario);
    printQueue(cenario->enemies);
    
    Position position0;
    position0.x = 10;
    position0.y = 10;
    position0.z = 0;
    printPosition(position0);
    
    refreshCenario(cenario, position0);
    printQueue(cenario->enemies);
    
    Ship *ship = createShip();
    printShip(ship);
    
    Key keyPressed = -1; /* Representa a tecla apertada */
    Position mousePosition;
    Shot *shipShot = NULL;
    int i;
    for (i = 0; ; i = (i + 1) % MAX_LOOP) {
        if (i % 20 == 0) {
            switch (keyPressed) {
                case UP:
                    moveShipVetically(ship, 1);
                    break;
                case DOWN:
                    moveShipVetically(ship, -1);
                    break;
                case RIGHT:
                    moveShipHorizontally(ship, 1);
                    break;
                case LEFT:
                    moveShipHorizontally(ship, -1);
                    break;
                case SPACE:
                    changeShipSpeed(ship, 1);
                    break;
                case CLICK:
                    scanf("%f %f %f", &mousePosition.x, &mousePosition.y, &mousePosition.z);
                    shipShot = shootFromShip(mousePosition, ship->position, 20);
                    break;
                default:
                    ship->velocity.x = 0;
                    ship->velocity.y = 0;
                    ship->velocity.z = INITIAL_VELOCITY;
                    break;
            }
            updateShipPosition(ship);
            insideKeeper(ship);
            
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

