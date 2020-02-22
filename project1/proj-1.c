/*
CSE 531 - Project 1. Submission by Sumit Rawat (ASU ID - 1216225348) and Harsh Virani (ASU ID - 1215137742)

Running instruction:

For compiling the program:
gcc -pthread -o proj-1 proj-1.c

To run the code:
./proj-1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

volatile int arr[3]={0,0,0};
semaphore_t wr_to_arr[3],print_arr,mutex;	// semaphores declaration : an array of semaphores for updating each element in the array once in 							every cycle, one for printing the array once and one mutex.

void update_array(int *arg)
{
  	int tId = *arg,i=0;
  	printf("Child thread %d started\n", tId);

  	while (1){
		P(&wr_to_arr[tId]);		//decrementing semaphores
    		P(&mutex);
    		arr[tId]++;			//incrementing the value of the array element
    		V(&mutex);
    		V(&print_arr);			//incrementingsemaphores
    		sleep(1);
	}
}

int main()
{
  	int id[3] = {0, 1, 2}, i;
	for(i=0;i<3;i++)
		init_sem(&wr_to_arr[i], 1);	//defining semaphore values
  	init_sem(&print_arr, 0);
  	init_sem(&mutex, 1);
	for(i=0;i<3;i++)
  		start_thread(update_array, &id[i]);	//creating 3 child thread

  	while(1) {
		for(i=0;i<3;i++)	
    			P(&print_arr);		//decrementing semaphore print_arr thrice as it gets incremented once during each update
    		P(&mutex);
		for(i=0;i<3;i++)    		
			printf("\t\tThe updated value of Array[%d] = %d\n", i,arr[i]); 		//printing the array
    		V(&mutex);
		for(i=0;i<3;i++)    		
			V(&wr_to_arr[i]);	//incrementing array of semaphores
		printf("============================================================\n");
		sleep(1); 
	}
  	return 0;
}
