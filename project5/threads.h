#include<stdio.h>
#include<ucontext.h>
#include "q.h"

#define STACK_SIZE 8192

TCB_t *Curr_Thread;
Queue *ReadyQ;
int counter = 0;

int getThreadID(TCB_t *item){
    return item->thread_id;
}

// Start thread function
void start_thread(void (*function)(void))
{
    	char *stack = (char *) malloc(STACK_SIZE*sizeof(char));
    	TCB_t *tcb = (TCB_t *) malloc(sizeof(TCB_t));
    	init_TCB(tcb, function, (void *) stack, STACK_SIZE);
    	tcb->thread_id = ++counter;
	AddQueue(ReadyQ,tcb);
}

// Run function
void run() 
{
    	Curr_Thread = DelQueue(ReadyQ);
    	ucontext_t parent;
    	getcontext(&parent);
    	swapcontext(&parent, &(Curr_Thread->context));
}

// Yield function
void yield()
{
	TCB_t *Prev_Thread;
    	AddQueue(ReadyQ, Curr_Thread);
    	Prev_Thread = Curr_Thread;
    	Curr_Thread = DelQueue(ReadyQ);	
    	if (Curr_Thread == NULL)
	{
		return;
    	}
    	swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));    
}

void thread_yeild(){
    while(1){
        yield();
    }
}
