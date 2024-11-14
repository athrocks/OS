#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *sourceFile, *destinationFile;
    char ch;
    char line[256];

    // Open source file in read mode
    sourceFile = fopen("source.txt", "r");
    if (sourceFile == NULL) {
        printf("Error opening source file.\n");
        return 1;
    }

    // Open destination file in write mode
    destinationFile = fopen("destination.txt", "w");
    if (destinationFile == NULL) {
        printf("Error opening destination file.\n");
        fclose(sourceFile);
        return 1;
    }

    // Copy character by character
    printf("Copying character by character:\n");
    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destinationFile);
        printf("%c", ch); // Print the character being copied
    }

    // Reset file pointer to the beginning for line-by-line copy
    rewind(sourceFile);

    // Copy line by line
    printf("\n\nCopying line by line:\n");
    while (fgets(line, sizeof(line), sourceFile) != NULL) {
        fputs(line, destinationFile);
        printf("%s", line); // Print the line being copied
    }

    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);

    printf("\nFile copied successfully.\n");
    return 0;
}
