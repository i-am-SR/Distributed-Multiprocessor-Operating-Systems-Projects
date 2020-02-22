#include "threads.h"

typedef struct Semaphore
{
	int counter;
	Queue *queue;
}Semaphore_t;

// initializes it to the InputValue and returns the pointer to the semaphore.
void initSem(Semaphore_t *sem, int InputValue)
{
	sem->queue = newQueue(sem->queue);
	sem->counter=InputValue;
}

// P(Semaphore_t * sem) - takes a pointer to a semaphore and performs P
void P(Semaphore_t *sem)
{
	TCB_t *previous_thread;
	sem->counter--;
	if(sem->counter<0) 
	{	
		AddQueue(sem->queue,Curr_Thread);
		previous_thread = Curr_Thread; 
		Curr_Thread = DelQueue(ReadyQ);
		swapcontext(&(previous_thread->context), &(Curr_Thread->context));
	}
}

//V(Semaphore_t * sem) - increments the semaphore
void V(Semaphore_t *sem)
{
	TCB_t *temp;
	sem->counter++;
	if(sem->counter<=0)
	{
		temp=DelQueue(sem->queue);
		AddQueue(ReadyQ,temp);
	}
	yield();
}
