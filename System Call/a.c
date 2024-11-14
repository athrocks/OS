#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    pid_t pid;
    int file_desc;
    char *filename = "output.txt";
    char *message = "Hello, this is a message written by system call.\n";

    // Create a new process
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) { // Child process
        printf("Child process created with PID: %d\n", getpid());
        printf("Child's Parent PID: %d\n", getppid());

        // Open a file for writing
        file_desc = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (file_desc < 0) {
            perror("File open failed");
            exit(1);
        }

        // Write to file using the write system call
        if (write(file_desc, message, sizeof(message)) < 0) {
            perror("File write failed");
            close(file_desc);
            exit(1);
        }

        // Close the file
        close(file_desc);

        // Replace the child process with a new program (using exec)
        execlp("ls", "ls", "-l", NULL); // Execute "ls -l" command
        perror("exec failed");
        exit(1);
    } else { // Parent process
        printf("Parent process with PID: %d\n", getpid());

        // Wait for the child process to complete
        wait(NULL);
        printf("Child process has completed.\n");
    }

    return 0;
}
