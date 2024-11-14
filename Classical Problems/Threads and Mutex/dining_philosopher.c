#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void* philosopher(void* num) {
    int id = *(int*)num;
    
    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);
        
        // Pick up the forks
        pthread_mutex_lock(&forks[id]); // Pick up left fork
        pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]); // Pick up right fork
        
        printf("Philosopher %d is eating.\n", id);
        sleep(1); // Eating
        
        // Put down the forks
        pthread_mutex_unlock(&forks[id]); // Put down left fork
        pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]); // Put down right fork
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    
    // Initialize mutexes for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Wait for philosophers to finish (they won't in this example)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Cleanup
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

