#ifndef _SHOT_QUEUE_H_
#define _SHOT_QUEUE_H_

#include <stdio.h>
#include "utils.h"
#include "shot.h"


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
void freeShotQueue(ShotQueue *queue);
void removeShotNode(ShotNode *node, ShotQueue *queue);

void enqueueShot(Shot *shot, ShotQueue *queue);
Shot* dequeueShot(ShotQueue *queue);
BOOL isShotQueueEmpty(ShotQueue *queue);
void updateShotQueue(ShotQueue *shotQueue);
void renderShotQ(ShotQueue *queue);
#endif

