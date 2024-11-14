#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;  // Buffer count

sem_t empty_slots;  // Semaphore to count empty slots in the buffer
sem_t full_slots;   // Semaphore to count filled slots
sem_t mutex;        // Mutex to protect buffer access

void* producer(void* arg) {
    int id = *(int*)arg;
    int item;

    while (1) {
        item = rand() % 100;
        
        sem_wait(&empty_slots); // Wait for an empty slot
        sem_wait(&mutex);       // Lock buffer access

        // Critical section: produce an item
        buffer[count] = item;
        count++;
        printf("Producer %d produced %d\n", id, item);

        sem_post(&mutex);       // Unlock buffer access
        sem_post(&full_slots);  // Increment count of full slots

        sleep(1); // Simulate production time
    }
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    int item;

    while (1) {
        sem_wait(&full_slots);  // Wait for a filled slot
        sem_wait(&mutex);       // Lock buffer access

        // Critical section: consume an item
        count--;
        item = buffer[count];
        printf("Consumer %d consumed %d\n", id, item);

        sem_post(&mutex);       // Unlock buffer access
        sem_post(&empty_slots); // Increment count of empty slots

        sleep(1); // Simulate consumption time
    }
}

int main() {
    pthread_t producers[2], consumers[2];
    int ids[2] = {1, 2};

    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create producer and consumer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&producers[i], NULL, producer, &ids[i]);
        pthread_create(&consumers[i], NULL, consumer, &ids[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    sem_destroy(&mutex);

    return 0;
}

