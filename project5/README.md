# CSE531_DMOS
Distributed/Multiprocessor Operating System Projects

Overview:

For this project you are to write build clients and one server that does file transfers. The clients can only upload files, and the server accepts file-name and file data from clients and writes them to files.

All ports are static. The client sends a message to the server port with a “filename” (string) and the file server changes that string to “filename.server”. The client then sends the file data to the server and the server writes the data to the file “filename.server”. (Note: The client may have to tell server file transfer is over).

Details:

1.      File server can do file receives simultaneously from multiple clients. Make the max number of concurrent transfers 3. If a fourth client tries, it should be told “do not do that”.

2.      Maximum file size is 1MB (approx), server enforces this.

3.      Maximum file length used by client – 15 chars, server enforces this (filename)

4.      Clients and servers do not share memory or file systems.

5.      Each client sends one file and then stops (see details below)

Assumptions and Tips:

1.      Do not assume server and client have access to each other’s files. Assume they are on different machines and do not share file systems.

2.      Do not change the message system (types, sizes, ports and so on). You may fix bugs and such.

3.      You can use a single threaded server, it is easier. If you do that, think about how to do a multi-threaded server.

Implementation strategies:

1.      Design the project first; do not start writing code without knowing how you will handle messages, filenames, dialogs between client and server, and all that.

2.      Make simplifying assumptions and start with simple implementations and then add features.

3.      Test every step.

4.      Note: This project is not simple and has many possibilities of programming issues/bugs. Please get started ASAP.

TEST PROGRAM REQUIREMENTS

[updated]

The program that you submit will be structured as follows:

1.      It is run from the command line, such as
%  ./a.out 5 f1 f2 f3 f4 f5
where 5 is the number of clients and f1…f5 are the files to transfer. You can assume the command line will be correct and you do not have to check for its structure (not checking is a security risk, but for this project it is ok).

2.      If the number of clients is higher than 3 then if the transfer of any of the 3 files have not been completed then the 4th (or 5th) one will be rejected.

3.      Each client transfers one file (once).

4.      After a client finishes sending a file over the server it executes “while (1) sleep() //wrong, see discussion board;” – because the termination of threads have not been implemented.

Simpler version: (50% of points)

You can do this version, just one client, and one file transferred (same as doing ./a.out 1 f1)

SUBMIT:

Your project must consist of 6 files:

1.      TCB.h  (uses ucontext.h)

2.      q.h   (includes TCB.h)

3.      threads.h  (includes q.h)

4.      sem.h (includes threads.h)

5.      msgs.h (includes sem.h)

6.      file_test.c – your test program (includes msgs.h).

(make sure the compile command, “gcc file_test.c” does the correct compilation).
