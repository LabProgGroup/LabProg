#include "utils.h"

typedef struct enemy Enemy;
struct enemy {
    int life; /*de 0 a 100*/
    Position position;
    int precison; /*de 0 a 10*/

};

int shouldShoot(Position shipP) {
    if distance(shipP, position) < 20
        return TRUE;
    return FALSE;
}

void gotShoot