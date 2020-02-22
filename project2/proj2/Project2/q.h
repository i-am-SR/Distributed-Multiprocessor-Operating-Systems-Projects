#include"TCB.h"

struct item
{
	struct item *next;
	struct item *prev;
	int val;
};

struct queue
{
  	struct TCB_t *head;
};
// returns a pointer to a new q-element, uses memory allocation
struct TCB_t* NewItem()
{
	struct TCB_t *item = (struct TCB_t*) malloc(sizeof(struct TCB_t));
	item->prev = NULL;
	item->next = NULL;
	return item;
}
// creates a empty queue, that is the header pointer is set to null.
struct queue* newQueue(struct queue *ReadyQ) 
{
   	ReadyQ = (struct queue *)malloc(sizeof(struct queue));
   	ReadyQ->head = NULL;
   	return ReadyQ;
}
// adds a queue item, pointed to by “item”, to the queue pointed to by head.
void AddQueue(struct queue *ReadyQ, struct TCB_t *tcb) 
{
	if(ReadyQ->head==NULL) 
	{
       		ReadyQ->head = tcb;
       		ReadyQ->head->next = ReadyQ->head;
       		ReadyQ->head->prev = ReadyQ->head;
   	}
	else 
	{
       		tcb->prev = ReadyQ->head->prev;
       		tcb->next = ReadyQ->head;
       		ReadyQ->head->prev->next = tcb; 
       		ReadyQ->head->prev = tcb;
   	}
}
// deletes an item from head and returns a pointer to the deleted item. If the queue is already empty, flag error.
struct TCB_t* DelQueue(struct queue *ReadyQ) 
{
	struct TCB_t *removed;
   	if(ReadyQ->head==NULL)
      		return NULL;
   	else 
	{
      		removed = ReadyQ->head;
      		if(ReadyQ->head->next == ReadyQ->head)
         	{
			printf("ERROR===== The queue is empty!!");			
			ReadyQ->head = NULL;
		}
      		else 
		{
      			ReadyQ->head = ReadyQ->head->next;
      			ReadyQ->head->prev = removed->prev;
      			removed->prev->next = ReadyQ->head;
      		}
      	return removed;
   	}
}


