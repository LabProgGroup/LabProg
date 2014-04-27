#include <stdio.h>
#include "utils.h"
#include "enemy.h"

typedef struct {
    Node *first;
    Node *last;
} Queue;

typedef struct {
    Enemy *enemy;
    Node *next;
} Node;

/* Cria uma queue vazia e a retorna */
Queue* createQueue();

/* insere um novo Node no final da fila */
void enqueue(Enemy *enemy);

/* tira um Node do inicio da fila */ 
Enemy* dequeue();

