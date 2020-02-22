/*
CSE 531 - Project 5. Submission by Sumit Rawat and Harsh Virani

Running instruction:

For compiling the program:
gcc file_test.c

To run the code: 
Make sure you have files f1, f2, f3, f4 and f5 in the curr directory(if you want to run 5 clients)
./a.out 5 f1 f2 f3 f4 f5
*/

#include "msgs.h"

int cl_counter=0, SERVER_PORT=0;
char** files;
int num_clients;
Semaphore_t mutex;

#define MAX_FILE_SIZE 1048576

// Function defining the actions of the client(s)
void client_fn(void)
{
	int cID, port;

    	P(&mutex); 
	cID = cl_counter;
    	port = cl_counter;
	cl_counter++;
    	char *filename = files[cID];
    	printf("<CLIENT %d>:[PORT#%d] Sending file %s to server \n",cID+1,port,filename);
    	V(&mutex);

    	struct message *msg_in, *msg_out;

    	// Client tries to establish connection with the server
    	msg_out = (struct message*) malloc(sizeof(struct message));
    	msg_out->arr_m[0] = port;
    	msg_out->arr_m[1] = 1;

    	printf("<CLIENT %d>:[PORT#%d] Connecting with server\n",cID,port);
    	while(1)
	{
      		send(SERVER_PORT,msg_out);
      		msg_in = rcv(port);   
      		if (msg_in->arr_m[0] == 2)
		{
        		printf("<CLIENT %d>:[PORT#%d] File : %s - File transfer request accepted\n",cID+1,port,filename);
        		break;
      		}
		else if (msg_in->arr_m[0] == 3)
		{
        		printf("<CLIENT %d>:[PORT#%d] File : %s - Retrying File transfer\n",cID+1,port,filename);
        		continue;
      		}
		else
		{
        		printf("<CLIENT %d>:[PORT#%d] File : %s - Unknown response from server for establishing connection request \n",cID+1,port,filename);
        		printf("Terminating client %d\n", cID+1);
        		thread_yeild();
      		}
 	}

    	// Connection established. Client sends file name.
    	msg_out->arr_m[1] = 4;
    	int mptr = 2;
    
    	for(int i = 0;i<strlen(filename);i++)
	{
      		msg_out->arr_m[mptr++] = filename[i];
      		if(mptr == MSG_SIZE)
		{
        		printf("<CLIENT %d>:[PORT#%d] File %s - Sending file content \n",cID+1,port,filename);
        		send(SERVER_PORT,msg_out);
        		msg_in = rcv(port);
        		if (msg_in->arr_m[0] == 5)
			{
          			printf("<CLIENT %d>:[PORT#%d] File %s - Server added file name \n",cID+1,port,filename);
          			mptr = 2;
        		}
			else if (msg_in->arr_m[0] == 6)
			{
          			printf("<CLIENT %d>:[PORT#%d] File : %s - File name exceeded 15 characters limit, aborting file transfer\n",cID+1,port,filename);
          			printf("Terminating client %d\n", cID+1);
          			thread_yeild();
        		}
			else
			{
          			printf("<CLIENT %d>:[PORT#%d] File : %s - Unknown response from server for file transfer request \n",cID+1,port,filename);
          			printf("Terminating client %d\n", cID+1);
          			thread_yeild();
        		}
      		}
    	}  
    	while(mptr != MSG_SIZE)
	{
      		msg_out->arr_m[mptr++] = -1;
    	}
    	msg_out->arr_m[1] = 11;
    	send(SERVER_PORT,msg_out);
    	msg_in = rcv(port);
    	if (msg_in->arr_m[0] == 5){}
	else if (msg_in->arr_m[0] == 6)
	{
      		printf("<CLIENT %d>:[PORT#%d] File %s - File name too long\n",cID+1,port,filename);
      		printf("File transfer cancelled! Client %d terminated.\n", cID+1);
      		thread_yeild();
    	}
//canrem
	else
	{
      		printf("<CLIENT %d>:[PORT#%d] File %s - Unknown response from server for file transfer request \n",cID+1,port,filename);
      		printf("Client %d terminated. \n", cID+1);
      		thread_yeild();
    	}
    
    	// Client starts transfer of file content to server
    	printf("<CLIENT %d>:[PORT#%d] File : %s - File transfer to server in progress\n",cID+1,port,filename);
    	msg_out->arr_m[0] = port;
    	msg_out->arr_m[1] = 7;
    	mptr = 2;
    	FILE* file = fopen(filename, "r"); 
    	int file_char;
    	while ((file_char = fgetc(file)) != EOF) 
	{
      	if(mptr == MSG_SIZE)
	{
	        send(SERVER_PORT,msg_out);
	        msg_in = rcv(port);
	        if (msg_in->arr_m[0] == 9)
		{
          		printf("<CLIENT %d>:[PORT#%d] File : %s - Server updated the file. \n",cID+1,port,filename);
			printf("<CLIENT %d>:[PORT#%d] File : %s - File transfer to server in progress\n",cID+1,port,filename);
          		mptr = 2;
        	}
		else if (msg_in->arr_m[0] == 10)
		{
          		printf("<CLIENT %d>:[PORT#%d] File : %s - File size exceeds 1MB!! File transfer cancelled.\n",cID+1,port,filename);
          		printf("Client %d terminated.\n", cID+1);
          		thread_yeild();
        	}
//canrem
		else
		{
          		printf("<CLIENT %d>:[PORT#%d] File : %s - Unknown response from server for file transfer request \n",cID+1,port,filename);
          		printf("Client %d terminated.\n",cID+1);
          		thread_yeild();
        	}
      	}	
      	msg_out->arr_m[mptr++] = file_char;
	}
    	while(mptr != MSG_SIZE)
	{
      		msg_out->arr_m[mptr++] = -1;
    	}
    	msg_out->arr_m[1] = 8;
    	send(SERVER_PORT,msg_out);
    	msg_in = rcv(port);
    	if (msg_in->arr_m[0] == 9){}
	else if (msg_in->arr_m[0] == 10)
	{
      		printf("<CLIENT %d>:[PORT#%d] File : %s - File transfer cancelled.\n",cID+1,port,filename);
      		printf("Client %d terminated.\n", cID+1);
      		thread_yeild();
    	}
	else
	{
      		printf("<CLIENT %d>:[PORT#%d] File : %s - Unknown response from server. \n",cID+1,port,filename);
      		printf("Client %d terminated.\n", cID+1);
      		thread_yeild();
    	}

    	fclose(file);
    	printf("<CLIENT %d>:[PORT#%d] File : %s - Transfer complete\n",cID+1, port, filename);
    	printf("<CLIENT %d>:[PORT#%d] Yields\n", cID+1, port);
    	thread_yeild();
}

// Function defining the actions of the server
void server_fn(void)
{
	struct message *msg_in;
	struct message *msg_out;

  	char client_files[num_clients][256];
  	int cl_cnt = 0;

  	while(1)
	{
  	char filename[22];
    	strcpy(filename,"");
    
  	printf("\t\t\t\t\t\t\t\t<SERVER>:[PORT#%d] Listening...\n",SERVER_PORT);
  	msg_in = rcv(SERVER_PORT);
    	int reply_port = msg_in->arr_m[0];
    	msg_out = (struct message*) malloc(sizeof(struct message));
  	if (msg_in->arr_m[1] == 1)
	{
      		if(cl_cnt == 3)
		{
        		msg_out->arr_m[0] = 3;
			printf("\t\t\t\t\t\t\t\t<SERVER>: File transfer request rejected! Too many clients.\n");
      		}
		else
		{
        	cl_cnt++;
        	msg_out->arr_m[0] = 2;
      	}
      	printf("\t\t\t\t\t\t\t\t<SERVER>: Sending reply to client on port %d \n",reply_port);
      	send(reply_port,msg_out);
    	}
	else if(msg_in->arr_m[1] == 11 || msg_in->arr_m[1] == 4)
	{
      		int close_file = 1;
      		memset(filename,0,sizeof(filename));
      		strcpy(filename,client_files[reply_port]);
      		int file_len = strlen(filename);
      		for(int i = 2; i < 10;i++)
		{
        		if(msg_in->arr_m[i] != -1)
			{
          			if(file_len >= 15)
				{
            				msg_out->arr_m[0] = 6;
            				close_file = 0;
            				cl_cnt--;
					printf("\t\t\t\t\t\t\t\t<SERVER>: File name too long. Cancelling file transfer on port %d\n",reply_port);
            				break;    
          			}
				else
				{
	            			filename[file_len++] = msg_in->arr_m[i];
          			}
        		}
      		}
      		if (close_file)
		{
          		msg_out->arr_m[0] = 5;
          		if(msg_in->arr_m[1] == 11)
			{
            			strcat(filename,".server");
          		}
		}
      		strcpy(client_files[reply_port],filename);
      		printf("\t\t\t\t\t\t\t\t<SERVER>: Sending reply to client on port %d \n",reply_port);
      		send(reply_port,msg_out);
    	}
	else if (msg_in->arr_m[1] == 7 || msg_in->arr_m[1] == 8)
	{
      		strcat(filename, client_files[reply_port]);
      		int close_file = 1;
      		FILE * file;
      		file = fopen(filename, "a");
      		for(int i = 2; i < 10;i++)
		{
        		if(msg_in->arr_m[i] != -1)
			{
          			int results = fputc(msg_in->arr_m[i], file);  
        		}
        		fseek(file, 0, SEEK_END);
        		unsigned long size = ftell(file);
        		if(size > MAX_FILE_SIZE)
			{
          			msg_out->arr_m[0] = 10;
          			fclose(file);
          			int err = remove(filename);
          			cl_cnt--;
				printf("<SERVER>: File size exceeds 1MB!! File transfer for port %d cancelled.\n", reply_port);
          			close_file = 0;
          			break;
        		}
      		}
      		if(close_file)
		{
          		msg_out->arr_m[0] = 9;
          		fclose(file);
          		if(msg_in->arr_m[1] == 8)
			{
            			cl_cnt--;
          		}
      		}
      		printf("\t\t\t\t\t\t\t\t<SERVER>: Sending reply to client on port %d \n",reply_port);
      		send(reply_port,msg_out);
    	}
	else
	{
      		printf("\t\t\t\t\t\t\t\tRequest type unknown. \n");
    	}
  	}
}

// Main function
int main(int argc, char* argv[])
{
	int i;
  	ReadyQ = newQueue(ReadyQ);
  	initSem(&mutex,1);
	num_clients = atoi(argv[1]);
	
	for(i = 0; i < num_clients; i++)
	{
    		init_port(i); 
	}

	SERVER_PORT = num_clients;
	init_port(SERVER_PORT);
	printf("Number of CLIENTS specified are : %d \n", num_clients);
	files = malloc((num_clients) * sizeof *files);
	start_thread(server_fn);
  	printf("Creating a SERVER\n");
	
	for(i = 0; i < num_clients; i++)
	{
	    	if(argv[i+2])
		{
	  		files[i] = malloc(strlen(argv[i+2])+1);
	  		strcpy(files[i], argv[i+2]);
		}
	}
	
	for(int i = 0; i < num_clients; i++)
	{
    		FILE * file;
    		file = fopen(argv[i+2], "r");
    		if(file) 
		{
		  	printf("Creating a CLIENT for the transfer of file %s\n", argv[i+2]);
		  	start_thread(client_fn);
    		}
		else 
		{
			if(argv[i+2])
			{
		    		printf("No such file exists (%s)!! \n", argv[i+2]);
        			printf("CLIENT creation cancelled!!\n");
		  	}
    		}
	}

  	run();
}


