
/*Uma fila cujo conteúdo é uma struct elements (ou enemy).
 * (Para Gustavo e Sesso, apagar depois):
 * Para inicializar as filas, use Queue q1 = newQueue();
 *                                Queue q2 = newQueue();
 *                                ...         
 * Para inserir um elemento: enqueue(e, q1);
 * Onde e é uma struct elements e q1 é uma das filas inicializadas.
 * 
 * Para desenfileirar um elemento: f = dequeue(q1); 
 * Onde f é uma struct elements e q1 é uma das filas inicializadas.
 * 
 * */               


/*
 * DECIDIR ISSO: Caso represente um elemento do cenário que não ataca 
 * ex: Uma árvore, life e precision assumem um valor negativo para indicar?
 *     Usamos outra struct?
 */
#include "utils.h"
/*Decidir se essa struct fica aqui || vai para utils || #include "enemy.h" */

/*Struct que define as defesas e os elementos do cenário.*/
typedef struct elements Elements; 
struct elements {
    int life;           
    Position position;  
    int damage;      
};

typedef struct queueNode* Link;
struct queueNode {
    Elements data;
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

/*Recebe uma struct Elements representando algum elemento do cenário e uma fila q. Essa
 * função enfila o elemento na fila q.
 */
void enqueue(Elements data, Queue q);

/*Essa função recebe uma fila q e retira o elemento que está há mais tempo na fila 
 * e o retorna. Se a fila estiver vazia, sai do programa com erro.
 */
Elements dequeue(Queue q);

/*Essa função recebe uma fila q, retira todos os elementos e desaloca toda a memória que era usada 
 * por essa fila. 
 */
void queueEmpty(Queue q);

/*Essa função recebe uma fila q e retorna o número de elementos dessa fila.*/
int queueSize(Queue q);











