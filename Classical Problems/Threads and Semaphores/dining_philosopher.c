#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];

void* philosopher(void* arg) {
    int id = *(int*)arg;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Pick up left fork
        sem_wait(&forks[id]);
        // Pick up right fork
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        // Put down right fork
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        // Put down left fork
        sem_post(&forks[id]);

        sleep(1); // Think before next round of eating
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
        ids[i] = i;
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}

