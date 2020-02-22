#include "sem.h"
#define MSGS_IN_PORT 10		//Number of messages in a port
#define NUM_OF_PORTS 100	//Total number of ports 
#define MSG_SIZE 10		//Number of integers in a message

// Declare a message type - contains an array of 10 integers, client_ID and reply port for the client.
typedef struct message
{
	int client_num;
	int reply_port;
	int m[MSG_SIZE];
}MESSAGE;


// Declare a port - contains N messages, N=10. Semaphores are associated with the port, for controlling synchronization.
/*
Using Strategy 2: A mutex semaphore, a producer semaphore and a consumer semaphore per port.
*/
struct port
{
	int write_ptr; 	// IN pointer
	int read_ptr;	// OUT pointer
	MESSAGE msg[MSGS_IN_PORT];
	Semaphore_t *producer, *consumer, *mutex;	
};

struct port set[NUM_OF_PORTS]; // Declaration of (100) ports
//Semaphore_t *mutex; 	

// Initialize all the 100 ports - Set the values for the semaphores and In and Out pointers for each port
void init_all_ports()
{
	int i;
	for(i=0; i<NUM_OF_PORTS; i++)
	{
		set[i].producer = init_sem(10);
		set[i].consumer = init_sem(0);
		set[i].mutex = init_sem(1);
		set[i].write_ptr=0;
		set[i].read_ptr=0;
	}
}

// Function to send message m1 to port p1
void send(struct port *p1, MESSAGE *m1)
{
	P(p1->producer);
	P(p1->mutex);
	int i;
	p1->msg[p1->write_ptr].client_num = m1->client_num;
	p1->msg[p1->write_ptr].reply_port = m1->reply_port;
	for(i=0; i<MSG_SIZE; i++)
	{
		p1->msg[p1->write_ptr].m[i] = m1->m[i];	
	}
	p1->write_ptr = (p1->write_ptr+1)%MSGS_IN_PORT;
	V(p1->mutex);
	V(p1->consumer);
}

// Function to receive message m1 from port p1
void rcv(struct port *p1, MESSAGE *m1)
{
	P(p1->consumer);	
	P(p1->mutex);
	int i;
	m1->client_num = p1->msg[p1->read_ptr].client_num;
	m1->reply_port = p1->msg[p1->read_ptr].reply_port; 
	for(i=0; i<MSG_SIZE; i++)
	{
		m1->m[i] = p1->msg[p1->read_ptr].m[i];	
	}
	p1->read_ptr = (p1->read_ptr+1)%MSGS_IN_PORT;
	V(p1->mutex);	
	V(p1->producer);
}





