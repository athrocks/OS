#include <stdio.h>

#define MAX_FRAMES 10

int isPresent(int frames[], int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == page) {
            return i;  // Page found at index
        }
    }
    return -1;  // Page not found
}

void updateFrames(int frames[], int n, int page) {
    for (int i = n - 1; i > 0; i--) {
        frames[i] = frames[i - 1];  // Shift pages to the right
    }
    frames[0] = page;  // Insert page at the front
}

int main() {
    int frames[MAX_FRAMES], referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);
    int pageFaults = 0;

    // Initialize frames
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        int pos = isPresent(frames, page);

        if (pos == -1) {
            updateFrames(frames, MAX_FRAMES, page);
            pageFaults++;
        } else {
            // Move the page to the front
            for (int j = pos; j > 0; j--) {
                frames[j] = frames[j - 1];
            }
            frames[0] = page;
        }
    }

    printf("Number of page faults: %d\n", pageFaults);
    return 0;
}
