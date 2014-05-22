#include "utils.h"

float clockTick = (float) 1/20;

Dimension defaultCenarioDim = {20, 20, 2000};
Dimension defaultEnemyDim = {4, 8, 4};

Position spaceTimeEquation(Position initialPosition, Velocity v) {
    Position newPosition = {
        initialPosition.x + v.x * clockTick,
        initialPosition.y + v.y * clockTick + (GRAVITY * clockTick * clockTick) / 2,
        initialPosition.z + v.z * clockTick,
    };
    
    return newPosition;
}

Velocity speedTimeEquation(Velocity initialVelocity) { 
    Velocity newVelocity = {
        initialVelocity.x,
        initialVelocity.y + GRAVITY * clockTick, 
        initialVelocity.z, 
    };
    
    return newVelocity;
}

float distance(Position a, Position b) { 
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}

/*Oops, não estou usando va e vb pra nada!*/
BOOL colisionTest(Position pa, Velocity va, float ra, Position pb, Velocity vb, float rb) {
	if (distance(pa, pb) < ra + rb)
		return TRUE;
	else
		return FALSE;
}
