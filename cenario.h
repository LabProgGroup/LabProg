#ifndef _CENARIO_H_
#define _CENARIO_H_
#include "queue.h"
#include "utils.h"

#define BUFFER_SIZE 1000
#define NUMBER_OF_ENEMIES 20

typedef struct {
    Queue *enemies;
    Dimension dimension;
} Cenario;

Cenario* createCenario();

void updateCenario(Cenario *cenario, Position shipPosition);

static void createNewEnemy(Cenario *cenario);

#endif
