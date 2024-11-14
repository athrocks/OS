#include <stdio.h>
#include <stdlib.h> // for rand func
#include <pthread.h>
#include <unistd.h> // for sleep func

#define BUFFER_SIZE 5  // Size of the buffer
int buffer[BUFFER_SIZE];  // Shared buffer
int count = 0;  // Number of items in the buffer

pthread_mutex_t mutex;  // Mutex for protecting buffer access
pthread_cond_t not_full; // Condition variable for buffer not full
pthread_cond_t not_empty; // Condition variable for buffer not empty

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {  // Produce 10 items
        // Produce an item
        sleep(rand() % 2);  // Simulate variable production time
        int item = rand() % 100;  // Produce a random item

        // Lock the mutex before accessing the buffer
        pthread_mutex_lock(&mutex);

        // Wait while the buffer is full
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &mutex);
        }

        // Add the item to the buffer
        buffer[count] = item;
        count++;
        printf("Produced: %d\n", item);

        // Signal that the buffer is not empty
        pthread_cond_signal(&not_empty);

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {  // Consume 10 items
        // Lock the mutex before accessing the buffer
        pthread_mutex_lock(&mutex);

        // Wait while the buffer is empty
        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }

        // Remove the item from the buffer
        int item = buffer[count - 1];
        count--;
        printf("Consumed: %d\n", item);

        // Signal that the buffer is not full
        pthread_cond_signal(&not_full);

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Simulate variable consumption time
        sleep(rand() % 2);
    }

    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize the mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    // Create the producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for the threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Clean up and destroy the mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}

