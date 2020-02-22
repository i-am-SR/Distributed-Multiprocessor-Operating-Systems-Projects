#include<stdlib.h>
#include "sem.h"

#define MSG_SIZE 10		//Number of integers in a message
#define NUM_OF_PORTS 100	//Total number of ports 

// Declare a message type - contains an array of 10 integers.
struct message
{
	int arr_m[MSG_SIZE];
};

// Declare a port - contains messages. Semaphores are associated with the port, for controlling synchronization.
struct port
{
    	int startptr; // IN pointer
    	int endptr;	// OUT pointer
	struct message *message_queue;
    	Semaphore_t producer, consumer, mutex;   
};

// Declaration of (100) ports
struct port set[NUM_OF_PORTS];

//Set the values for the semaphores and In and Out pointers for a port
void init_port(int index){
    	initSem(&(set[index].mutex), 1);
    	initSem(&(set[index].producer), 10);
    	initSem(&(set[index].consumer), 0); 
	set[index].startptr = 0;
    	set[index].endptr = 0;
    	set[index].message_queue = (struct message *) malloc (10 * sizeof(struct message));  
}

// Function to send message msg to port port_num
void send(int port_num, const struct message *msg)
{
    	P(&(set[port_num].producer));
    	P(&(set[port_num].mutex)); 
    	set[port_num].message_queue[set[port_num].endptr] = *msg;
    	set[port_num].endptr = (set[port_num].endptr + 1)%10;  
    	V(&(set[port_num].mutex));
    	V(&(set[port_num].consumer));
}

// Function to receive message from port port_num
struct message* rcv(int port_num)
{
    	struct message *msg;
    	P(&set[port_num].consumer);
    	P(&set[port_num].mutex);
    	msg =&(set[port_num].message_queue[set[port_num].startptr]);
    	set[port_num].startptr = (set[port_num].startptr + 1)%10;
    	V(&set[port_num].mutex);
    	V(&set[port_num].producer);
    	return msg;
}


