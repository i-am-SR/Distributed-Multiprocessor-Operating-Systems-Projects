#include "TCB.h"

static TCB_t *ReadyQ = NULL;
TCB_t *item = NULL;
// returns a pointer to a new q-element, uses memory allocation
TCB_t * NewItem(TCB_t *item)
{
 	item = (TCB_t*) malloc(sizeof(TCB_t));
	item->next = NULL;
	item->prev = NULL;
	return item;
}
// creates a empty queue, that is the header pointer is set to null.
TCB_t *newQueue()
{
	ReadyQ = malloc(sizeof(TCB_t));
	ReadyQ->next = ReadyQ;
	ReadyQ->prev = ReadyQ;
	return ReadyQ;	
}

// adds a queue item, pointed to by “item”, to the queue pointed to by head.
void AddQueue(TCB_t *ReadyQ, TCB_t *node)
{
  	//Checks whether queue is empty and if it is sets the header node of the queue
  	if(ReadyQ->prev == ReadyQ && ReadyQ->next == ReadyQ)
  	{
      		ReadyQ->next = node;
      		ReadyQ->prev = node;
      		node->next = ReadyQ;
      		node->prev = ReadyQ;
  	}
	//Adding elements to the queue
	else
 	{
    		ReadyQ->prev->next =node;
    		node->prev=ReadyQ->prev;
    		ReadyQ->prev = node;
    		node->next = ReadyQ;
 	}
}

// deletes an item from head and returns a pointer to the deleted item. If the queue is already empty, flag error.
TCB_t* DelQueue(TCB_t *ReadyQ)
{
	TCB_t *temp = NULL;	
	if(ReadyQ == ReadyQ->prev && ReadyQ == NULL) 	// check for empty queue
	{
		printf("Cannot Delete from empty queue");
		return NULL;
	}
	else
	{
		temp = ReadyQ->next;
		ReadyQ->next = ReadyQ->next->next;
		ReadyQ->next->prev = ReadyQ;
	}
	return temp;
}

