#ifndef _CENARIO_H_
#define _CENARIO_H_

#include "enemyQueue.h"
#include "utils.h"
#include "ship.h"
#include "shotQueue.h"
typedef struct {
    EnemyQueue *enemies;
    Dimension dimension;
} Cenario;

Cenario* createCenario(Dimension dimension);
void refreshCenario(Cenario *cenario, Position shipPosition);
void createNewEnemyInInterval(float min, float max, Cenario *cenario);
void initEnemies(Cenario *cenario);

BOOL verifyShipColision(Ship *ship, Cenario *cenario);
BOOL verifyShipShotColision(Cenario *cenario, ShotQueue *shotQueue);
BOOL verifyEnemiesShotColision(Cenario *cenario, ShotQueue *shotQueue, Ship *sh);
void rmFarShots(ShotQueue *shotQ, Cenario *cenario);
void renderBackground();
void renderCenario();
#endif


