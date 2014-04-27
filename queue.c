#import "queue.h"

Queue* createQueue() {
    Queue *queue = malloc(sizeof(Queue));
    
    queue->head = malloc(sizeof(Node));
    queue->head->next = queue->head;
    queue->head->enemy = NULL;
    
    queue->lastNode = queue->head;
    queue->first = NULL;
    queue->last  = NULL;
    
    return queue;
}

void enqueue(Enemy *enemy, Queue *queue) {
    Node *newNode = malloc(sizeof(Node));
    
    newNode->enemy = enemy;
    newNode->next  = queue->head;

    queue->lastNode->next = newNode;
    queue->lastNode = newNode;
    
    queue->last = queue->lastNode->enemy;
    queue->first = queue->head->next->enemy;
}

Enemy* dequeue(Queue *queue) {
    Node *firstNode = queue->head->next;
    Enemy *enm = firstNode->enemy;
    
    queue->head->next = firstNode->next;
    
    queue->first = queue->head->next->enemy;
    
    if (firstNode == queue->lastNode) {
        queue->lastNode = queue->head;
        queue->last = NULL;
    }
    if (firstNode != queue->head)
        free(firstNode);
    
    return enm;
}