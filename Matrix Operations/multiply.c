#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 3 // Rows in Matrix A
#define N 2 // Columns in Matrix A  and Rows in Matrix B
#define P 3 // Columns in matrix B

int A[M][N] = { {1, 2}, {3, 4}, {5, 6} }; // Matrix A
int B[N][P] = { {7, 8, 9}, {10, 11, 12} }; // Matrix B

int result[M][P]; // Resultant Matrix

typedef struct {
    int row;
    int col;
} ThreadData;

void* multiply(void* arg){
    ThreadData* data = (ThreadData*)arg;
    
    int row = data->row;
    int col = data->col;
    
    result[row][col] = 0;
    
    for(int k=0; k<N ;k++){
        result[row][col] += A[row][k] * B[k][col]; // Perform multiplication and addition
    }
    
    pthread_exit(NULL); // Exit the thread
}

int main()
{
    pthread_t resultant[M][P];
    ThreadData thread_data[M][P]; // array to hold data for each thread
    
    for(int i=0; i< M;i++){
        for(int j=0; j<P;j++){
            thread_data[i][j].row = i;
            thread_data[i][j].col = j;
            
            pthread_create(&resultant[i][j], NULL, multiply, (void*)&thread_data[i][j]);
        }
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            pthread_join(resultant[i][j], NULL); // Join thread
        }
    }
    
    // Print the resultant matrix C
    printf("Resultant Matrix C:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    
	return 0;
}



