// Thread creation and joining
// Creates multiple threads using pthread. Each thread prints a message. Main thread joins all threads.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    printf("Thread %d is running.\n", thread_id);
    // Perform some work in the thread
    sleep(5);
    printf("Thread %d is done.\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;

    // Create threads
    // pthread_create - thread creation,
    // #include <pthread.h>
    // int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    // void *(*start_routine)(void*), void *arg);


    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            fprintf(stderr, "Error creating thread %d.\n", i);
            exit(1);
        }
    }

    // Wait for threads to finish
    // The pthread_join() function provides a simple mechanism allowing 
    // an application to wait for a thread to terminate. After the thread
    // terminates, the application may then choose to clean up resources
    // that were used by the thread.
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have completed.\n");

    return 0;
}

/*
toor@LAPTOP-RLTA9ELC:~/system_progs$ gcc -pthread 4-thread_simple.c
toor@LAPTOP-RLTA9ELC:~/system_progs$ ./a.out
Thread 3 is running.
Thread 2 is running.
Thread 1 is running.
Thread 0 is running.
Thread 3 is done.
Thread 2 is done.
Thread 1 is done.
Thread 0 is done.
All threads have completed.

toor@LAPTOP-RLTA9ELC:~/system_progs$
*/
