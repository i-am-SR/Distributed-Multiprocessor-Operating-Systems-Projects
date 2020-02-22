#include "q.h"
#define STACK_SIZE 8192

static TCB_t *Curr_Thread;
static TCB_t *ReadyQ;
static TCB_t thread;

// Start thread function
void start_thread(void (*function)(void))
{
	TCB_t *context;
	context = malloc(sizeof(TCB_t));
	stack_t *stackP = malloc(STACK_SIZE*sizeof(stack_t));
	init_TCB(context,function,stackP,STACK_SIZE*sizeof(stack_t));
	thread.thread_id++;
	printf("In main: creating thread %d\n",thread.thread_id);
	if(ReadyQ == NULL) //if Run Queue is empty
	{ 
		ReadyQ = newQueue();
    	}
	item = NewItem(item);
	item->context=context->context;
	AddQueue(ReadyQ,item);      
}

// Run function
void run() 
{
    	Curr_Thread = DelQueue(ReadyQ);
    	ucontext_t parent;
    	getcontext(&parent);	//gets the current context of the calling process, 
		//stores it in the ucontext struct pointed to by ucp.
    	swapcontext(&parent, &(Curr_Thread->context));	//save the current user context in the context structure 
		//and restore the user context structure of parent.
}

// Yield function
void yield()
{
	TCB_t *Prev_Thread;
	//ucontext_t curr_context;	
	AddQueue(ReadyQ, Curr_Thread); 
    	Prev_Thread = Curr_Thread;
    	Curr_Thread = DelQueue(ReadyQ);
	swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));	//save the current user context in the context structure 
		//and restore the user context structure of parent.
}
