#ifndef _CENARIO_H_
#define _CENARIO_H_
#include "queue.h"
#include "utils.h"
#include "ship.h"

#define BUFFER_SIZE 1000
#define MAX_DISTANCE_BETWEEN_ENEMIES 20

typedef struct {
    Queue *enemies;
    Dimension dimension;
} Cenario;

Cenario* createCenario(float x, float y, float z);

void refreshCenario(Cenario *cenario, Position shipPosition);

static void createNewEnemyInInterval(float min, float max, Cenario *cenario);

static void initEnemies(Cenario *cenario);

int verifyShipColision(Ship *ship, Cenario *cenario);

int verifyShotColision(Shot *shot, Cenario *cenario);
#endif
