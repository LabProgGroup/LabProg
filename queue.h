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