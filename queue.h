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

/* Cria uma queue vazia e a retorna */
Queue* createQueue();

/* insere um novo Node no final da fila */
void enqueue(Enemy *enemy, Queue *queue);

/* tira um Node do inicio da fila */ 
Enemy* dequeue(Queue *queue);

void removeNode(Node *node, Queue *queue);

#endif