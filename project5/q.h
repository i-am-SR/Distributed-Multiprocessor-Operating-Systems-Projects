#include "TCB.h"

typedef struct Queue
{
	TCB_t *header;
}Queue;

int isEmpty(Queue *Q) 
{
   	if(Q->header->next == Q->header)
      		return 1;
   	return 0;
}

// creates a empty queue, that is the header pointer is set to null.
Queue* newQueue(Queue *Q)	
{
	Q = (Queue *)malloc(sizeof(Queue));
	Q->header = (TCB_t *)malloc(sizeof(TCB_t));
	Q->header->thread_id = -1;
	Q->header->next=Q->header;
	Q->header->prev=Q->header;
	return Q;
}

// adds a queue item, pointed to by “item”, to the queue pointed to by head.
void AddQueue(Queue *Q,  TCB_t *item)
{
	if(isEmpty(Q))
	{
	Q->header->next = item;
	Q->header->prev= item;
        item->prev= Q->header;
        item->next= Q->header;	
	}
	else
	{
	item->next= Q->header;
        item->prev=Q->header->prev;
	Q->header->prev->next=item;
        Q->header->prev=item;
	}
}

// deletes an item from head and returns a pointer to the deleted item. If the queue is already empty, flag error.
TCB_t* DelQueue(Queue *Q)	
{
	TCB_t *item;

	if(isEmpty(Q))
	{			
		return NULL;	
	}
	else
	{
		item = Q->header->next;
		Q->header->next=Q->header->next->next;
		Q->header->next->prev=Q->header;
	}
	item->next = NULL;
	item->prev = NULL;
	return item;
}

// returns a pointer to a new q-element, uses memory allocation
TCB_t* newItem() 
{
	TCB_t *item= (TCB_t *) malloc(sizeof(TCB_t));
	return item;
}
