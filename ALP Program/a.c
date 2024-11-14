#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 100  // Size of main memory (can be changed as needed)

void loadALPToMemory(const char *filename, char memory[MEMORY_SIZE][256]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        exit(1);
    }

    int i = 0;
    while (i < MEMORY_SIZE && fgets(memory[i], 256, file) != NULL) {
        // Remove newline character if present
        memory[i][strcspn(memory[i], "\n")] = '\0';
        i++;
    }

    fclose(file);
}

void printMemory(char memory[MEMORY_SIZE][256]) {
    printf("Main Memory Content:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i][0] != '\0') {
            printf("Memory[%d]: %s\n", i, memory[i]);
        }
    }
}

int main() {
    char memory[MEMORY_SIZE][256] = {0};  // Main memory initialized to null strings
    const char *filename = "alp_program.txt";  // Input ALP file

    loadALPToMemory(filename, memory);
    printMemory(memory);

    return 0;
}
