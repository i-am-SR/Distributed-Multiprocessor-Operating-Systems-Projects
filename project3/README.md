# CSE531_DMOS
Distributed/Multiprocessor Operating System Projects

Overview:

For this project you are to write routines that implements semaphores and then use them to implement the readers/writers problem.

Step 1:

Declare a semaphore type (name it Semaphore_t) . The semaphore is a counter and a queue of TCBs. Semaphores declared/used in the end program will be of this type.

Step 2:

Implement the routines

Semaphore_t CreateSem(int InputValue) // mallocs a semaphore structure, initializes it to the InitValue and returns the pointer to the semaphore.

void P(Semaphore_t * sem)  // takes a pointer to a semaphore and performs P, i.e. decrements the semaphore, and if the value is less than zero then blocks the thread in the queue associated with the semaphore.

void V(Semaphore_t * sem)  // increments the semaphore, and if the value is 0 or negative,
then takes a PCB out of the semaphore queue and puts it into the ReadyQ.
Note: The V routine also "yields" to the next runnable thread.

-- put the code in a file called “sem.h”. Of course you need to include threads.h into this file (to get access to yield) and threads includes tcb.h.

 

Step 3:

Test the semaphore implementation using simple test routines. Test it more by using a producer-consumer program. (The semaphore testing program will only include sem.h, which includes the other files, transitively).  – Do NOT submit

Step 4:

Modify the p-threads implementation of readers and writers and run it with your implementation of semaphores. Submit this program.

SUBMIT:

Your project must consist of 5 files:

1.      TCB.h  (uses ucontext.h)

2.      q.h   (includes TCB.h)

3.      threads.h  (includes q.h)

4.      sem.h (includes threads.h)

5.      read_write.c – must contain your name(s) in comments @ beginning

(make sure the compile command, “gcc read_write.c” does the correct compilatio
