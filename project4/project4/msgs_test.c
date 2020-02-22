/*
CSE 531 - Project 4. Submission by Sumit Rawat (ASU ID - 1216225348) and Harsh Virani (ASU ID - 1215137742)

Running instruction:

For compiling the program:
gcc msgs_test.c

To run the code:
./a.out
*/

#include "msgs.h"
#define SERVER_PORT 0		// Server port is set to 0
#define INCL_SLEEP 1		// Flag to include or remove sleep statements
#define NUMBER_OF_CLIENTS 3	// 3 clients are being used

// Function defining the actions of the client(s)
void fn_client(int *a)
{
	while(1)
	{
		int i, arg = *a;
		MESSAGE m1;
		m1.client_num = arg;
		m1.reply_port = arg+50;   // The reply port for a client is its (50+Client_ID) - 51 cl1, 52 for cl2 and so on
		printf("<CLIENT %d>: Sending to SERVER on port %d[%d]...\n", m1.client_num, SERVER_PORT, set[SERVER_PORT].write_ptr);
		printf("MSG [");
		/* Generating the message. For client 1 it is [10, 11, 12,....., 19], for client 2 it is [20, 21,..., 29] and so on */
		for(i=0; i<MSG_SIZE; i++)
		{
			m1.m[i] = arg*10+i;
			printf("%d",m1.m[i]);
			if(i != MSG_SIZE-1)
			{
				printf(", ");
			}			
		}
		printf("]");
		printf("\n");
		if(INCL_SLEEP)		
		{sleep(1);}
		send(&set[SERVER_PORT], &m1);
		printf("<CLIENT %d>: Send successful!\n", arg);
		if(INCL_SLEEP)		
		{sleep(1);}
		rcv(&set[m1.reply_port], &m1);
		printf("<CLIENT %d>: Receiving from SERVER on port %d[%d]...\n", m1.client_num, m1.reply_port, set[m1.reply_port].read_ptr-1);
		printf("REPLY [");
		for(i=0; i<MSG_SIZE; i++)
		{
			printf("%d",m1.m[i]);
			if(i != MSG_SIZE-1)
			{
				printf(", ");
			}			
		}
		printf("]\n");
		printf("<CLIENT %d>: Receive successful!\n", arg);		
		if(INCL_SLEEP)		
		{sleep(1);}
	}
}

// Function defining the actions of the server(s)
void fn_server(int x)
{
	while(1)
	{
		int i, rp;
		MESSAGE m1;
		rcv(&set[SERVER_PORT], &m1);
		printf("\t\t\t\t\t\t\t\t<SERVER>: Receiving from CLIENT %d on port %d[%d]...\n", m1.client_num, SERVER_PORT, set[SERVER_PORT].read_ptr-1);
		printf("\t\t\t\t\t\t\t\tMSG [");
		for(i=0; i<MSG_SIZE; i++)
		{
			printf("%d",m1.m[i]);
			if(i != MSG_SIZE-1)
			{
				printf(", ");
			}			
		}
		printf("]\n");
		printf("\t\t\t\t\t\t\t\t<SERVER>: Receive successful!\n");
		rp = m1.reply_port;
		if(INCL_SLEEP)		
		{sleep(1);}
		printf("\t\t\t\t\t\t\t\t<SERVER>: Generating reply...\n");
		/* Generating the reply for client. To each integer in the message, add (100*client_ID) */		
		for(i=0; i<MSG_SIZE; i++)
		{
			m1.m[i] += (1000*m1.client_num);			
		}
		if(INCL_SLEEP)		
		{sleep(1);}
		printf("\t\t\t\t\t\t\t\t<SERVER>: Sending reply to CLIENT %d on port %d[%d]...\n", m1.client_num, rp, set[m1.reply_port].write_ptr);
		send(&set[rp], &m1);
		printf("\t\t\t\t\t\t\t\tREPLY [");
		for(i=0; i<MSG_SIZE; i++)
		{
			printf("%d",set[rp].msg[set[rp].write_ptr-1].m[i]);
			if(i != MSG_SIZE-1)
			{
				printf(", ");
			}			
		}
		printf("]\n");
		printf("\t\t\t\t\t\t\t\t<SERVER>: Send successful!\n");
		if(INCL_SLEEP)		
		{sleep(1);}
	}
}

int main()
{
	//mutex = init_sem(1);
	int client_nums[NUMBER_OF_CLIENTS], i;
	init_all_ports();
	for(i=1; i<=NUMBER_OF_CLIENTS; i++)
	{
		client_nums[i-1]=i;
		printf("Creating a CLIENT\n");
    		start_thread(fn_client, &client_nums[i-1]);
	}
	printf("Creating a SERVER\n");
    	start_thread(fn_server, NULL);
	run();
}


