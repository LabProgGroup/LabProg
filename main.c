#include <stdio.h>
#include "cenario.h"
#include "queue.h"
#include "enemy.h"
#include "utils.h"

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
        printf("\n\tNode: %p %p %p", (void *)node, (void *)node->enemy, (void *)node->next);
        node = node->next;
    }
    printf("\n");
}

void printPosition(Position position) {
    printf("\nPosition:\n\tx: %f\n\ty: %f\n\tz: %f\n", position.x, position.y, position.z);
}

void printEnemy(Enemy *enemy) {
    printf("\nEnemy:\n\t%p\n\tlife: %d\n\tprecision: %d", enemy, enemy->life, enemy->precision);
    printPosition(enemy->position);
}

int main(int argc, const char * argv[])
{
    Cenario *cenario = createCenario();
    cenario->dimension.x = 20;
    cenario->dimension.y = 40;
    cenario->dimension.z = 2000;
    printCenario(cenario);
    printQueue(cenario->enemies);
    
    Position position;
    position.x = 5;
    position.y = 6;
    position.z = 7;
    printPosition(position);
    
    
    Enemy *enemy = createEnemy(position, 8);
    printEnemy(enemy);
    
    enqueue(enemy, cenario->enemies);
    printQueue(cenario->enemies);
    
    Enemy *enemy2 = createEnemy(position, 8);
    enqueue(enemy2, cenario->enemies);
    printQueue(cenario->enemies);
    
    Enemy *enemyTest = dequeue(cenario->enemies);
    printEnemy(enemyTest);
    printQueue(cenario->enemies);
    
    enemyTest = dequeue(cenario->enemies);
    printEnemy(enemyTest);
    printQueue(cenario->enemies);
    
    enemyTest = dequeue(cenario->enemies);
    printf("\nNão consegue dequeue na head: %p\n", (void *)enemyTest);
    printQueue(cenario->enemies);
    
    enqueue(enemy, cenario->enemies);
    enqueue(enemy2, cenario->enemies);
    printQueue(cenario->enemies);
    
    updateCenario(cenario, position);
    printQueue(cenario->enemies);
    printEnemy(cenario->enemies->last);
    
    return 0;
}

