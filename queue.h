#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include "utils.h"
#include "enemy.h"

typedef struct enemynode EnemyNode;
struct enemynode{
    Enemy *enemy;
    EnemyNode *next;
};

typedef struct {
    Enemy *first;
    Enemy *last;
    
    EnemyNode *head;
    EnemyNode *lastNode;
} EnemyQueue;

EnemyQueue* createEnemyQueue();
void removeEnemyNode(EnemyNode *node, EnemyQueue *queue);

void enqueueEnemy(Enemy *enemy, EnemyQueue *queue);
Enemy* dequeueEnemy(EnemyQueue *queue);
BOOL isEnemyQueueEmpty(EnemyQueue *queue);

#endif