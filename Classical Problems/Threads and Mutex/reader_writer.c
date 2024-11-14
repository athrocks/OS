#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for sleep fucntion

pthread_mutex_t read_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource_mutex = PTHREAD_MUTEX_INITIALIZER;

int reader_count = 0;

void* reader(void* arg){
    int id = *(int*)arg;
    
    // Lock read_mutex to safely update reader_count
    pthread_mutex_lock(&read_mutex);
    reader_count++;
    
    // If this is the first reader, lock resource_mutex to block writers
    if(reader_count == 1){
        pthread_mutex_lock(&resource_mutex);
    }
    pthread_mutex_unlock(&read_mutex);
    
    // Reading section
    printf("Reader %d is reading the shared resource.\n", id);
    sleep(1);  // Simulate reading time

    // Reading completed
    pthread_mutex_lock(&read_mutex);
    reader_count--;
    
    // If this is the last reader, unlock resource_mutex to allow writers
    if (reader_count == 0) {
        pthread_mutex_unlock(&resource_mutex);
    }
    pthread_mutex_unlock(&read_mutex);
    
    return NULL;
}

void* writer(void *arg){
    int id = *(int*)arg;
    
    // Lock resource_mutex to get exclusive access to the resource
    pthread_mutex_lock(&resource_mutex);
    
    // Writing section
    printf("Writer %d is writing to the shared resource.\n", id);
    sleep(1);  // Simulate writing time
    
    pthread_mutex_unlock(&resource_mutex);  // Release exclusive access

    return NULL;
   
}

int main()
{
    pthread_t readers[5] , writers[2];
    int reader_ids[5] = {1,2,3,4,5};
    int writer_ids[2] = {1,2};
    
    // Create reader threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    
    // Destroy the mutexes
    pthread_mutex_destroy(&read_mutex);
    pthread_mutex_destroy(&resource_mutex);

    return 0;
}
