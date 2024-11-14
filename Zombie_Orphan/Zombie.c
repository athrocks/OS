#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process sleeps to keep the child process as a zombie
        printf("Parent process PID: %d\n", getpid());
        sleep(10);  // Sleep to let the child become a zombie
    } else if (pid == 0) {
        // Child process exits immediately
        printf("Child process PID: %d\n", getpid());
        exit(0);
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}

