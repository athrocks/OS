#include <stdio.h>
#include <pthread.h>

// Define a structure to hold the parameters and the result
typedef struct {
    int a;
    int b;
    int result;
} SumArgs;


// Original sum function
int sum(int a, int b);

// Thread fucntion
void* thread_sum(void* arg){
    
    // Cast the argument back to SumArgs*
    SumArgs* args = (SumArgs*)arg;
    
    // Call the sum function and store the result in the structure
    args->result = sum(args->a, args->b);

    // End the thread
    pthread_exit(NULL);
    
}

int main()
{
    pthread_t thread1;
    
    // Initialize the arguments structure
    SumArgs args;
    args.a = 5;  // Example value
    args.b = 10; // Example value
    
    if (pthread_create(&thread1, NULL, thread_sum, &args) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    
    // Wait for the thread to finish
    pthread_join(thread1, NULL);

    // Print the result stored in the structure
    printf("The result of sum(%d, %d) is %d\n", args.a, args.b, args.result);

    
    return 0;
}

int sum(int a, int b) {
    return a + b;
}