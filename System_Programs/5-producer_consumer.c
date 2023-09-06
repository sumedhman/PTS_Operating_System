// Thread synchronization
// Classic concurrency problem of producer-consumer. Uses mutex locks and condition variables for synchronized access to shared buffer.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int buffer_index = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Locks a mutex object, which identifies a mutex
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER; // Initialize a Condition Variable
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER; // Initialize a Condition Variable

void *producer(void *arg) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        item = rand() % 100;  // Generate a random item
        pthread_mutex_lock(&mutex);
        while (buffer_index == BUFFER_SIZE) {
            pthread_cond_wait(&buffer_not_full, &mutex);
        }
        buffer[buffer_index++] = item;
        printf("Produced item: %d\n", item);
        pthread_cond_signal(&buffer_not_empty);
        pthread_mutex_unlock(&mutex);
        usleep(100000);  // Sleep for a short time, durarion in micro-seconds
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex);
        while (buffer_index == 0) {
            pthread_cond_wait(&buffer_not_empty, &mutex);
        }
        item = buffer[--buffer_index];
        printf("Consumed item: %d\n", item);
        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&mutex);
        usleep(150000);  // Sleep for a slightly longer time, durarion in micro-seconds
    }
    pthread_exit(NULL);
}

int main() {
    // pthread_t is the data type used to uniquely identify a thread
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    printf("All producers and consumers have finished.\n");

    return 0;
}

/*
toor@LAPTOP-RLTA9ELC:~/system_progs$ gcc 5-producer_consumer.c
toor@LAPTOP-RLTA9ELC:~/system_progs$ ./a.out
Produced item: 83
Consumed item: 83
Produced item: 86
Consumed item: 86
Produced item: 77
Produced item: 15
Consumed item: 15
Consumed item: 77
Produced item: 93
Produced item: 35
Consumed item: 35
Consumed item: 93
Produced item: 92
Produced item: 86
Produced item: 49
Produced item: 21
Consumed item: 21
Consumed item: 49
Produced item: 62
Produced item: 27
Consumed item: 27
Consumed item: 62
Produced item: 90
Produced item: 59
Produced item: 63
Consumed item: 63
Produced item: 26
Consumed item: 26
Produced item: 40
Consumed item: 40
Produced item: 26
Consumed item: 26
Produced item: 72
Consumed item: 72
Produced item: 36
Consumed item: 36
Consumed item: 59
Consumed item: 90
Consumed item: 86
Consumed item: 92
All producers and consumers have finished.
toor@LAPTOP-RLTA9ELC:~/system_progs$
*/
