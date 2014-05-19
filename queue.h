#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include "utils.h"
#include "enemy.h"

typedef struct node Node;
struct node{
    Enemy *enemy;
    Node *next;
};

typedef struct {
    Enemy *first;
    Enemy *last;
    
    Node *head;
    Node *lastNode;
} Queue;

Queue* createQueue();
void removeNode(Node *node, Queue *queue);

void enqueue(Enemy *enemy, Queue *queue);
Enemy* dequeue(Queue *queue);

#endif