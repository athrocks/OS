#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 3 // Rows in Matrix A
#define N 3 // Columns in Matrix A and Rows in Matrix B
#define P 3 // Columns in Matrix B

int A[M][N] = { {1, 2,3}, {4, 5, 6}, {7, 8, 9} }; // Matrix A
int B[N][P] = { {10, 11, 12}, {13, 14, 15} , {16, 17, 18}}; // Matrix B

int result[M][P]; // Resultant Matrix
int add_result[M][P]; // Addition Result
int sub_result[M][P]; // Subtraction Result

typedef struct {
    int row;
    int col;
} ThreadData;

// Matrix multiplication
void* multiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int row = data->row;
    int col = data->col;

    result[row][col] = 0;
    for (int k = 0; k < N; k++) {
        result[row][col] += A[row][k] * B[k][col];
    }
    
    pthread_exit(NULL);
}

// Matrix addition
void* add(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int row = data->row;
    int col = data->col;

    add_result[row][col] = A[row][col] + B[row][col];
    pthread_exit(NULL);
}

// Matrix subtraction
void* subtract(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int row = data->row;
    int col = data->col;

    sub_result[row][col] = A[row][col] - B[row][col];
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[M][P];
    ThreadData thread_data[M][P];

    // Perform matrix multiplication
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            thread_data[i][j].row = i;
            thread_data[i][j].col = j;
            pthread_create(&threads[i][j], NULL, multiply, (void*)&thread_data[i][j]);
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Perform matrix addition
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            pthread_create(&threads[i][j], NULL, add, (void*)&thread_data[i][j]);
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Perform matrix subtraction
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            pthread_create(&threads[i][j], NULL, subtract, (void*)&thread_data[i][j]);
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Print the resultant matrices
    printf("Resultant Matrix (Multiplication):\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    printf("\nResultant Matrix (Addition):\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", add_result[i][j]);
        }
        printf("\n");
    }

    printf("\nResultant Matrix (Subtraction):\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", sub_result[i][j]);
        }
        printf("\n");
    }

    return 0;
}

