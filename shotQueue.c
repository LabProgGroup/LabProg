#include "shotQueue.h"
#include "shot.h"

ShotQueue* createShotQueue() {
    ShotQueue *shotQueue = malloc(sizeof(ShotQueue));
    
    shotQueue->head = malloc(sizeof(ShotNode));
    shotQueue->head->next = shotQueue->head;
    shotQueue->head->shot = NULL;
    
    shotQueue->lastNode = shotQueue->head;
    shotQueue->first = NULL;
    shotQueue->last  = NULL;
    
    return shotQueue;
}

void removeShotNode(ShotNode *node, ShotQueue *st) {
    ShotNode *actualNode = st->head;
    while (actualNode->next != st->head) {
        if (actualNode->next == node) {
            actualNode->next = node->next;

            if (actualNode->next == st->head) {
                st->lastNode = actualNode;
                st->last = actualNode->shot;
            }
            st->first = st->head->next->shot;

            freeShot(node->shot);
            free(node);
            return;
        }
        actualNode = actualNode->next;
    }
}

void enqueueShot(Shot *st, ShotQueue *shotQueue) {
    ShotNode *newNode = malloc(sizeof(ShotNode));
    
    newNode->shot = st;
    newNode->next  = shotQueue->head;

    shotQueue->lastNode->next = newNode;
    shotQueue->lastNode = newNode;
    
    shotQueue->last = shotQueue->lastNode->shot;
    shotQueue->first = shotQueue->head->next->shot;
}

Shot* dequeueShot(ShotQueue *shotQueue) {
    ShotNode *firstNode = shotQueue->head->next;
    Shot *st = firstNode->shot;
    
    shotQueue->head->next = firstNode->next;
    
    shotQueue->first = shotQueue->head->next->shot;
    
    if (firstNode == shotQueue->lastNode) {
        shotQueue->lastNode = shotQueue->head;
        shotQueue->last = NULL;
    }
    
    return st;
}

BOOL isShotQueueEmpty(ShotQueue *shotQueue) {
    return shotQueue->first == NULL;
}

void renderShotQ(ShotQueue *queue) {
    int i =0;
    ShotNode* sn = queue->head->next;
    Shot* sh = sn->shot;
    while (sh != NULL) {
        printf("tentei desenhar! %d\n", i);
        i++;
        renderShot(sn->shot);
        sn = sn->next;
        sh = sn->shot;
    }

}
