#include "q.h"
#define STACK_SIZE 8192

struct TCB_t *Curr_Thread = '\0';
struct queue *ReadyQ;
static int counter = 0;
// Start thread function
void start_thread(void (*function)(void))
{
    	char *stack = (char *) malloc(STACK_SIZE*sizeof(char));
    	struct TCB_t *tcb = NewItem();
    	init_TCB(tcb, function, (void *) stack, STACK_SIZE);
    	tcb->thread_id=++counter;
    	AddQueue(ReadyQ,tcb);	
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
    	struct TCB_t *Prev_Thread;
    	AddQueue(ReadyQ, Curr_Thread); 
    	Prev_Thread = Curr_Thread;
    	Curr_Thread = DelQueue(ReadyQ);
    	swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));	//save the current user context in the context structure 
		//and restore the user context structure of parent.
}
//Print the thread ID
void printTID(struct TCB_t *tcb)
{
	printf("Thread ID: %d",tcb->thread_id);
}

