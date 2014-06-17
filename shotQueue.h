#ifndef _SHOT_QUEUE_H_
#define _SHOT_QUEUE_H_

#include <stdio.h>
#include "utils.h"
#include "shot.h"
<<<<<<< HEAD

// #define foreachshot(item, list) 
//     ShotNode *nd; 
=======
/*
// #define foreachshot(item, list) \
//     ShotNode *nd; \
>>>>>>> 669e79b207597a847346e34e0c34e4027ae9465d
//     for (nd = list->head->next, item = nd->shot; nd != list->head; nd = nd->next, item = nd->shot)
*/

typedef struct shotnode ShotNode;
struct shotnode{
    Shot *shot;
    ShotNode *next;
};

typedef struct {
    Shot *first;
    Shot *last;
    
    ShotNode *head;
    ShotNode *lastNode;
} ShotQueue;

ShotQueue* createShotQueue();
void removeShotNode(ShotNode *node, ShotQueue *queue);

void enqueueShot(Shot *shot, ShotQueue *queue);
Shot* dequeueShot(ShotQueue *queue);
BOOL isShotQueueEmpty(ShotQueue *queue);
void updateShotQueue(ShotQueue *shotQueue);
void renderShotQ(ShotQueue *queue);
void rmFarShots(float shipZ, ShotQueue *shotQ);
void updateShotQueue(ShotQueue *shotQueue);
#endif
