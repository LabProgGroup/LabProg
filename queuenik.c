#include <stdio.h>
#include <stdlib.h>

typedef struct queueNode* Link;
struct queueNode {
    void* data;
    Link next;
};

struct queue {
    Link first;
    Link last;
};

typedef struct queue* Queue;
/*Recebe um ponteiro genérico e um ponteiro em uma lista ligada, que compõe uma fila.
 *Ela aloca uma nova célula e insere na fila.
 */
static Link new(void* data, Link next);

/*Essa função recebe um ponteiro para uma lista ligada e retorna o número de elementos dessa lista.*/
static int size(Link link);

/*Recebe um ponteiro genérico e um ponteiro em uma lista ligada, que compõe uma fila.
 *Ela aloca uma nova célula e insere na fila.
 */
static Link new(void* data, Link next) {
    Link link = (Link) malloc(sizeof(*link));
    link->data = data;
    link->next = next;
    return link;
}

/*Cria uma nova fila e retorna seu ponteiro. */
Queue newQueue() {
    Queue q = (Queue) malloc(sizeof *q);
    q->first = q->last = NULL;
    return q;
}

/*Recebe uma fila q e retorna TRUE se essa fila estiver vazia e FALSE se tiver ao menos 
 * um elemento nela.
 */
int queueIsEmpty(Queue q) {
    return q->first == NULL;
}

/*Recebe um ponteiro genérico e uma fila q. Essa
 * função enfileira o ponteiro na fila q.
 */
void enqueue(void* data, Queue q) {
    if (queueIsEmpty(q)) {
        q->last = new(data, NULL);
        q->first = q->last;
        return;
    }
    q->last->next = new(data, NULL);
    q->last = q->last->next;
} 

/*Essa função recebe uma fila q e retira o elemento que está há mais tempo na fila 
 * e o retorna. Se a fila estiver vazia, sai do programa com erro.
 */
void* dequeue(Queue q) {
    if (queueIsEmpty(q)) {
        printf("Fila vazia! ");
        exit(EXIT_FAILURE);
    }
    void* data = q->first->data;
    Link tmp = q->first->next;
    free(q->first);
    q->first = tmp;
    return data;
}

/*Essa função recebe uma fila q, retira todos os elementos e desaloca toda a memória que era usada 
 * por essa fila. 
 */
void queueEmpty(Queue q) {
    while (q->first != NULL)
       dequeue(q);
    free(q);
}   

/*Essa função recebe uma fila q e retorna o número de elementos dessa fila.*/
int queueSize(Queue q) {
   if (q->first == NULL) return 0;
   return size(q->first); 
}

/*Essa função recebe um ponteiro para uma lista ligada e retorna o número de elementos dessa lista.*/
static int size(Link link) {
   if (link->next == NULL) return 1;
   return (size(link->next) + 1);
}
