#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process terminates
        printf("Parent process PID: %d exiting\n", getpid());
        exit(0);
    } else if (pid == 0) {
        // Child process continues to execute
        sleep(5);  // Sleep to allow parent to terminate first
        printf("Child process PID: %d, Parent PID: %d\n", getpid(), getppid());
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}

