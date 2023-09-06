// Concept of zombie processes, Uses fork()
// Child process exits immediately after fork(), becomes a zombie. Parent sleeps to demonstrate zombie process behavior.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // Create a child process
    pid_t pid = fork();
    if (pid > 0) {
        // This is the parent process.
        // Sleep for a while to allow the child process to exit.
	printf("This is parent process: %d, its parent: %d\n", getpid(), getppid());
	printf("Doing longer task. Will end after 30 seconds\n");
        sleep(30);
	printf("Completed parent process task (PID: %d)\n", getpid());
    } else if (pid == 0) {
        // This is the child process.
        // Exit immediately.
	printf("This is child process: %d, its parent: %d\n", getpid(), getppid());
	printf("Terminating immediately\n");
        exit(0);
    } else {
        // fork() failed.
        return 1;
    }

    return 0;
}

/*
toor@LAPTOP-RLTA9ELC:~/system_progs$ gcc 2-zombie_test.c
toor@LAPTOP-RLTA9ELC:~/system_progs$ ./a.out
This is parent process: 252, its parent: 11
Doing longer task. Will end after 30 seconds
This is child process: 253, its parent: 252
Terminating immediately
Completed parent process task (PID: 252)
toor@LAPTOP-RLTA9ELC:~/system_progs$ ps
  PID TTY          TIME CMD
   11 pts/0    00:00:00 bash
  255 pts/0    00:00:00 ps
toor@LAPTOP-RLTA9ELC:~/system_progs$ ./a.out &
[1] 256
toor@LAPTOP-RLTA9ELC:~/system_progs$ This is parent process: 256, its parent: 11
Doing longer task. Will end after 30 seconds
This is child process: 257, its parent: 256
Terminating immediately
ps
  PID TTY          TIME CMD
   11 pts/0    00:00:00 bash
  256 pts/0    00:00:00 a.out
  257 pts/0    00:00:00 a.out <defunct>
  258 pts/0    00:00:00 ps
toor@LAPTOP-RLTA9ELC:~/system_progs$ Completed parent process task (PID: 256)

[1]+  Done                    ./a.out
toor@LAPTOP-RLTA9ELC:~/system_progs$ ps
  PID TTY          TIME CMD
   11 pts/0    00:00:00 bash
  259 pts/0    00:00:00 ps
toor@LAPTOP-RLTA9ELC:~/system_progs$
When the parent process is sleeping for 30 seconds then open another terminal
and run the command 'ps -a', check the presence of defunct or zombie prcess status.
*/
