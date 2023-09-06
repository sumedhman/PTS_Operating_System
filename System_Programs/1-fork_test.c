// Process creation and process ids
// Creates child process using fork(). Prints process ids to distinguish parent and child processes.

#include<stdio.h>
#include<unistd.h>

int main(){
    // create a variable to hold the process id
    int pid = fork();
    printf("PID = %d\n", pid);
    if(pid){    // non-zero pid for parent
        printf("This is parent process: %d, its parent: %d\n", getpid(), getppid());
    } else {    // zero pid for child process
        printf(":This is child process: %d, its parent: %d\n", getpid(), getppid());
    }

    pid = fork();
    printf(":PID = %d\n", pid);
    if(pid){    // non-zero pid for parent
        printf("::This is parent process: %d, its parent: %d\n", getpid(), getppid());
    } else {    // zero pid for child process
        printf(":::This is child process: %d, its parent: %d\n", getpid(), getppid());
    }
    
    getchar();

    return 0;
}

/*
toor@LAPTOP-RLTA9ELC:~/system_progs$ gcc 1-fork_test.c
toor@LAPTOP-RLTA9ELC:~/system_progs$ ./a.out
PID = 10917
This is parent process: 10916, its parent: 9399
:PID = 10918
::This is parent process: 10916, its parent: 9399
:PID = 0
:::This is child process: 10918, its parent: 10916
PID = 0
:This is child process: 10917, its parent: 10916
:PID = 10919
::This is parent process: 10917, its parent: 10916
:PID = 0
:::This is child process: 10919, its parent: 10917

toor@LAPTOP-RLTA9ELC:~/system_progs$
    9399
     |
   10916 (Current Process)
    /  \
 10917 10918 (Child Processes)
   |
 10919   (Child Process)
*/
