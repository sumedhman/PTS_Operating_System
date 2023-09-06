// IPC using pipes
// Parent writes messages to pipe. Child process reads from pipe to receive messages from parent.

// Example from the ebook System-Programming UNIX/LINUX, page 133

// A pipe is a mechanism for interprocess communication; data written to the pipe by
// one process can be read by another process. The data is handled in a first-in, 
// first-out (FIFO) order. The pipe has no name; it is created for one use and bot
// ends must be inherited from the single process which created the pipe.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int pd[2], n, i;
char line[256];

int main()
{
	char msg[] = "I AM YOUR PARENT";
	int size = strlen(msg);

	pipe(pd); // create a pipe
	printf("pd=[%d, %d]\n", pd[0], pd[1]);
	if (fork())
	{ // fork a child to share the pipe
		printf("parent %d close pd[0]\n", getpid());
		close(pd[0]); // parent as pipe WRITER (PRODUCER), closing the reading end of the pipe
		while (i++ < 10)
		{ // parent writes to pipe 10 times
			printf("parent %d writing to pipe\n", getpid());
			
			n = write(pd[1], msg, size);
			printf("parent %d wrote %d bytes to pipe\n", getpid(), n);
			sleep(1);
		}
		printf("parent %d exit\n", getpid());
	}
	else
	{
		printf("child %d close pd[1]\n", getpid());
		close(pd[1]); // child as pipe READER (CONSUMER), closing the writing end of the pipe
		while (1)
		{ // child read from pipe
			printf("child %d reading from pipe\n", getpid());
			if ((n = read(pd[0], line, 128)))
			{ // try to read 128 bytes
				line[n] = 0;
				printf("child read %d bytes from pipe: %s\n", n, line);
			}
			else // pipe has no data and no writer
				exit(0);
		}
	}
}

/*
toor@LAPTOP-RLTA9ELC:~/system_progs$ gcc 6-parent_child_pipe.c
toor@LAPTOP-RLTA9ELC:~/system_progs$ ./a.out
pd=[3, 4]
parent 334 close pd[0]
parent 334 writing to pipe
parent 334 wrote 16 bytes to pipe
child 335 close pd[1]
child 335 reading from pipe
child read 16 bytes from pipe: I AM YOUR PARENT
child 335 reading from pipe
parent 334 writing to pipe
parent 334 wrote 16 bytes to pipe
child read 16 bytes from pipe: I AM YOUR PARENT
child 335 reading from pipe
parent 334 writing to pipe
parent 334 wrote 16 bytes to pipe
child read 16 bytes from pipe: I AM YOUR PARENT
child 335 reading from pipe
parent 334 writing to pipe
parent 334 wrote 16 bytes to pipe
child read 16 bytes from pipe: I AM YOUR PARENT
child 335 reading from pipe
parent 334 writing to pipe
parent 334 wrote 16 bytes to pipe
child read 16 bytes from pipe: I AM YOUR PARENT
child 335 reading from pipe
parent 334 writing to pipe
parent 334 wrote 16 bytes to pipe
child read 16 bytes from pipe: I AM YOUR PARENT
child 335 reading from pipe
parent 334 writing to pipe
parent 334 wrote 16 bytes to pipe
child read 16 bytes from pipe: I AM YOUR PARENT
child 335 reading from pipe
parent 334 writing to pipe
parent 334 wrote 16 bytes to pipe
child read 16 bytes from pipe: I AM YOUR PARENT
child 335 reading from pipe
parent 334 writing to pipe
parent 334 wrote 16 bytes to pipe
child read 16 bytes from pipe: I AM YOUR PARENT
child 335 reading from pipe
parent 334 writing to pipe
parent 334 wrote 16 bytes to pipe
child read 16 bytes from pipe: I AM YOUR PARENT
child 335 reading from pipe
parent 334 exit
toor@LAPTOP-RLTA9ELC:~/system_progs$
*/
