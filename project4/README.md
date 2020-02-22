# CSE531_DMOS
Distributed/Multiprocessor Operating System Projects

Overview:

For this project you are to write build a module that does message passing via ports.

Step 1:

Declare a port. A port is something that contains N messages, make N=10. There would be semaphores associated with the port, for controlling synchronization. The port “contains” messages hence a port may be a pointer to a Q of messages, or an array of messages.

Declare a message type. For simplicity, a message is an array of 10 integers.

Declare a set (array of ports). The ports are numbered 0 to 99.

Step 2:

Implement the routines

Send (with appropriate arguments). The send is a “blocking” asynchronous send that is: it places the message in the port and returns but blocks if port is full.

 

Receive (with appropriate arguments). The receive is a “blocking” receive.

 

Put the code in msgs.h, and include sem.h in the file msgs.h

 

Step 3:

Test the message passing system by writing one (or more) servers and having several clients talk to the servers.

 

Implementation strategies:

Strategy 1: A mutex semaphore for all ports, and a producer semaphore and a consumer semaphore - per port

Strategy 2: Same as 1, but a mutex per port.

Strategy 3: 1 mutex + 1 producer + 1 consumer semaphore for every 10 ports. This is more coarse grained, saves on number of semaphores and is desirable in some kernel implementations. It is also considerably more difficult to get right. Wrong implementations may even work!

Instructions: Start with strategy 1, then move to strategy 2. You are required to do strategy 2. You are strongly encouraged to do strategy 3, after 2 works.

SUBMIT:

Your project must consist of 6 files:

1.      TCB.h  (uses ucontext.h)

2.      q.h   (includes TCB.h)

3.      threads.h  (includes q.h)

4.      sem.h (includes threads.h)

5.      msgs.h (includes sem.h)

6.      msgs_test.c – your test program.

(make sure the compile command, “gcc msgs_test.c” does the correct compilation).

