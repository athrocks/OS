#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t mutex;       // Controls access to reader_count
sem_t write_lock;  // Ensures only one writer or multiple readers

int reader_count = 0;  // Count of readers currently reading

void* reader(void* arg) {
    int id = *(int*)arg;
    
    while (1) {
        sem_wait(&mutex);      // Lock access to reader_count
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&write_lock); // First reader locks the write_lock
        }
        sem_post(&mutex);      // Unlock access to reader_count
        
        // Reading section
        printf("Reader %d is reading.\n", id);
        sleep(1);  // Simulate reading time

        sem_wait(&mutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&write_lock); // Last reader unlocks write_lock
        }
        sem_post(&mutex);

        sleep(1); // Simulate time between reads
    }
}

void* writer(void* arg) {
    int id = *(int*)arg;
    
    while (1) {
        sem_wait(&write_lock); // Ensure no readers/writers in critical section

        // Writing section
        printf("Writer %d is writing.\n", id);
        sleep(1); // Simulate writing time

        sem_post(&write_lock); // Allow others to access the resource

        sleep(2); // Simulate time between writes
    }
}

int main() {
    pthread_t readers[5], writers[2];
    int ids[5] = {1, 2, 3, 4, 5};

    sem_init(&mutex, 0, 1);
    sem_init(&write_lock, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}

