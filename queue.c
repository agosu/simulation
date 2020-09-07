#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
void create (queue *Que1)                          /*Sukuriama eilė*/
{                                                   
    *Que1 = NULL;
}
int enqueue (queue *Que1, queue_data n_data)       /*Elementas pridedadamas prie eilės*/
{                                                   /*Dirbama su nuorodomis į adresus*/ 
    queue temp = (queue)malloc(sizeof(queue));
    queue last = *Que1;
    if(temp == NULL) 
        return false;
    temp->data = n_data;                             /*Įkeliama informacija*/
    temp->next = NULL;
    if(*Que1 == NULL)
    {
        *Que1 = temp;
        return true;
    }
    while(last->next != NULL)                       /*Einama prie paskutinio elemento*/
        last = last->next;
    last->next = temp;
    return true;
}
int dequeue (queue *Que1, queue_data *deq)          /*Elementas išimamas iš eilės*/
{                                                   /*Dirbama su nuorodomis į adresus*/ 
    queue temp = *Que1;                             /*'temp' laikina vieta, kuri neleis prarasti adresų*/;
    if(*Que1 == NULL)
        return false;
    *deq = (*Que1)->data;
    if(temp != NULL)
    {
        *Que1 = (*Que1)->next;
        free(temp);
    }
    return true;
}
int isEmpty(queue Que1)                            /*Patikrinama, ar eilė tuščia ar ne*/
{                                                   /*Dirbama su paprastomis nuorodomis, nes nereikia duomenų*/
    if(Que1 == NULL)                                /*Eilė bus tuščia, kai bus lygu NULL*/
        return true;
    else
        return false;    
}
int isFull(queue Que1)
{
    queue temp = (queue)malloc(sizeof(queue));
    if(temp == NULL)
        return true;
    else
    {
        free(temp);
        return false;
    }
}
int destroy(queue *Que1)                           /*Eilė sunaikinama*/
{                                                   /*Dirbama su nuorodomis į adresus*/
    queue place;                                   /*'place' laikina vieta, kuri neleis prarasti adresų*/
    if(*Que1 == NULL) 
        return false;                                          
    while((place = *Que1) != NULL)                  /*Kol nėra lygu NULL, bus atlaisvinama atmintis*/
    {
        *Que1 = (*Que1)->next;
        free(place);
    }
    *Que1 = NULL;
    return true;
}