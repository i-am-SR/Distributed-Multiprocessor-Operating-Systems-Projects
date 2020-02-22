#include "threads.h"

typedef struct Semaphore_t 
{
	int count;
	TCB_t *Queue;
}Semaphore_t;

// Routine 1: CreateSem(int InputValue) - mallocs a semaphore structure, 
// initializes it to the InitValue and returns the pointer to the semaphore.

Semaphore_t* init_sem(int InputValue)
{   
	Semaphore_t* s = (Semaphore_t*)malloc(sizeof(Semaphore_t));
	if(s != NULL)
	{
    		s->count = InputValue;
		s->Queue = newQueue();
	}
	return s;
}

// Routine 2: P(Semaphore_t * sem) - takes a pointer to a semaphore and performs P

void P(Semaphore_t *sem)
{   
	sem->count--;
	//printf("Count: %d\n", sem->count);
    	if (sem->count < 0)
	{
		TCB_t *Prev_Thread;
		AddQueue(sem->Queue, Curr_Thread);
		Prev_Thread = Curr_Thread;
    		Curr_Thread = DelQueue(ReadyQ);	
		swapcontext(&(Prev_Thread->context),&(Curr_Thread->context));
	}
}


// Routine 3: V(Semaphore_t * sem) - increments the semaphore, and if the value is 0 or negative,
// then takes a PCB out of the semaphore queue and puts it into the ReadyQ.

void V(Semaphore_t * sem)
{   
    	sem->count++;
    	if (sem->count <= 0) 
	{
		AddQueue(ReadyQ, DelQueue(sem->Queue));
	}
	yield(); // The V routine also "yields" to the next runnable thread.
}


