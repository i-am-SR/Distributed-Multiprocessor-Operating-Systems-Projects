#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<string.h>
#include<unistd.h>

typedef struct TCB_t 
{
      	struct TCB_t *prev;
      	struct TCB_t *next;
      	ucontext_t context;
	int thread_id;	
}TCB_t;

void init_TCB(TCB_t *tcb, void *function, void *stackP, int stack_size, int *arg)
{
     	memset(tcb,'\0',sizeof(TCB_t)); 	//fill a block of memory => 
		//memset(Starting address of memory to be filled,Value to be filled,Number of bytes)     
	getcontext(&tcb->context);	//gets the current context of the calling process, 
		//stores it in the ucontext struct pointed to by ucp.
     	tcb->context.uc_stack.ss_sp = stackP;
     	tcb->context.uc_stack.ss_size  = (size_t) stack_size;	//allocate a new stack for this context
		//ucontext_t type is a structure that includes: uc_stack -> the stack used by this context
	makecontext(&tcb->context, function, 1, arg);	//modify the context specified by ucp
}
