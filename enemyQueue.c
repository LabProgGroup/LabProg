#include "enemyQueue.h"

EnemyQueue* createEnemyQueue() {
    EnemyQueue *queue = malloc(sizeof(EnemyQueue));
    
    queue->head = malloc(sizeof(EnemyNode));
    queue->head->next = queue->head;
    queue->head->enemy = NULL;
    
    queue->lastNode = queue->head;
    queue->first = NULL;
    queue->last  = NULL;
    
    return queue;
}

void removeEnemyNode(EnemyNode *node, EnemyQueue *queue) {
    EnemyNode *actualNode = queue->head;
    while (actualNode->next != queue->head) {
        if (actualNode->next == node) {
            actualNode->next = node->next;

            if (actualNode->next == queue->head) {
                queue->lastNode = actualNode;
                queue->last = actualNode->enemy;
            }
            queue->first = queue->head->next->enemy;

            free(node->enemy);
            free(node);
            return;
        }
    }
}

void enqueueEnemy(Enemy *enemy, EnemyQueue *queue) {
    EnemyNode *newNode = malloc(sizeof(EnemyNode));
    
    newNode->enemy = enemy;
    newNode->next  = queue->head;

    queue->lastNode->next = newNode;
    queue->lastNode = newNode;
    
    queue->last = queue->lastNode->enemy;
    queue->first = queue->head->next->enemy;
}

Enemy* dequeueEnemy(EnemyQueue *queue) {
    EnemyNode *firstNode = queue->head->next;
    Enemy *enm = firstNode->enemy;
    
    queue->head->next = firstNode->next;
    
    queue->first = queue->head->next->enemy;
    
    if (firstNode == queue->lastNode) {
        queue->lastNode = queue->head;
        queue->last = NULL;
    }
    
    return enm;
}

BOOL isEnemyQueueEmpty(EnemyQueue *queue) {
    return queue->first == NULL;
}
