#ifndef _CENARIO_H_
#define _CENARIO_H_

#include "queue.h"
#include "utils.h"
#include "ship.h"

typedef struct {
    EnemyQueue *enemies;
    Dimension dimension;
} Cenario;

Cenario* createCenario(Dimension dimension);
void refreshCenario(Cenario *cenario, Position shipPosition);

static void createNewEnemyInInterval(float min, float max, Cenario *cenario);
static void initEnemies(Cenario *cenario);
BOOL verifyShipColision(Ship *ship, Cenario *cenario);
BOOL verifyShotColision(Shot *shot, Cenario *cenario);
BOOL isInsideCenario(Position position, Cenario *cenario);

#endif
