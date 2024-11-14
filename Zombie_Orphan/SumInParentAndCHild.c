#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int even_sum = 0, odd_sum = 0;

    pid_t pid = fork();

    if (pid > 0) {
        // Parent process calculates the sum of even numbers
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) {
                even_sum += arr[i];
            }
        }
        printf("Parent process (PID: %d) - Sum of even numbers: %d\n", getpid(), even_sum);
        
        // Wait for child process to finish
        wait(NULL);
    } else if (pid == 0) {
        // Child process calculates the sum of odd numbers
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 != 0) {
                odd_sum += arr[i];
            }
        }
        printf("Child process (PID: %d) - Sum of odd numbers: %d\n", getpid(), odd_sum);
        exit(0);
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}

