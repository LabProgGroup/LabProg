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

/*Cria uma nova fila e retorna seu ponteiro. */
Queue newQueue();

/*Recebe uma fila q e retorna TRUE se essa fila estiver vazia e FALSE se tiver ao menos 
 * um elemento nela.
 */
int queueIsEmpty(Queue q);

/*Recebe um ponteiro genérico e uma fila q. Essa
 * função enfileira o ponteiro na fila q.
 */
void enqueue(void* data, Queue q);

/*Essa função recebe uma fila q e retira o elemento que está há mais tempo na fila 
 * e o retorna. Se a fila estiver vazia, sai do programa com erro.
 */
void* dequeue(Queue q);

/*Essa função recebe uma fila q, retira todos os elementos e desaloca toda a memória que era usada 
 * por essa fila. 
 */
void queueEmpty(Queue q);

/*Essa função recebe uma fila q e retorna o número de elementos dessa fila.*/
int queueSize(Queue q);
