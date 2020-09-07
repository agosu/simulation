#ifdef __cplusplus
extern "C" {
#endif

#ifndef queue_h_included
#define queue_h_included
#include "queue_data.h"
#define true 1
#define false 0
typedef struct Queue{
    queue_data data;
    struct Queue* next;
} queue1;
typedef queue1* queue;
void create(queue *Que1);              /*Eilės sukūrimas*/
int enqueue(queue *Que1, queue_data info);             /*Elemento pridėjimas*/
int dequeue(queue *Que1, queue_data *deq);             /*Elemento išėmimas*/
int isEmpty(queue Que1);              /*Tuščia ar ne*/
int isFull(queue Que1);               /*Pilna ar ne*/
int destroy(queue *Que1);             /*Eilės naikinimas*/
#endif


#ifdef __cplusplus
#endif // __cplusplus
