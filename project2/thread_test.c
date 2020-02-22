/*
CSE 531 - Project 2. Submission by Sumit Rawat and Harsh Virani

Running instruction:

For compiling the program:
gcc -o thread_test thread_test.c

To run the code:
./thread_test
*/


#include "threads.h"

int global=0;

void func1()
{
   	int local = 0;
    	while (1)
	{
		printTID(ReadyQ->head);
        	printf(" |		global:= %d local:= %d\n", global++, local++);
        	sleep(1);
        	yield();      
    	}
}  

void func2()
{
   	int local = 0;
	while (1)
	{
		printTID(ReadyQ->head);
        	printf(" |		global:= %d local:= %d\n", global++, local++);
        	sleep(1);
        	yield();
    	}
}    

void func3()
{
   	int local = 0;
    	while (1)
	{
		printTID(ReadyQ->head);
        	printf(" |		global:= %d local:= %d\n", global++, local++);
        	sleep(1);
        	yield();
	}
}   

int main()
{  
    	ReadyQ=newQueue(ReadyQ);
    	start_thread(func1);
    	start_thread(func2);
    	start_thread(func3);
    	run();
    	return 1;
}
