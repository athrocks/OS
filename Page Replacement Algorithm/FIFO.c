#include <stdio.h>

#define MAX_FRAMES 10

int isPresent(int frames[], int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == page) {
            return 1;  // Page found in frames
        }
    }
    return 0;  // Page not found
}

int main() {
    int frames[MAX_FRAMES], referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);
    int pageFaults = 0, index = 0;

    // Initialize frames
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        if (!isPresent(frames, page)) {
            frames[index] = page;
            index = (index + 1) % MAX_FRAMES;  // Move to next frame index in circular order
            pageFaults++;
        }
    }

    printf("Number of page faults: %d\n", pageFaults);
    return 0;
}
