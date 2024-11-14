#include <stdio.h>

#define MAX_FRAMES 10

// Find the farthest future occurrence of a page
int findFarthest(int frames[], int n, int referenceString[], int currentIndex) {
    int farthest = -1, index = -1;
    for (int i = 0; i < n; i++) {
        int j;
        for (j = currentIndex; j < sizeof(referenceString) / sizeof(referenceString[0]); j++) {
            if (frames[i] == referenceString[j]) {
                break;
            }
        }
        if (j == sizeof(referenceString) / sizeof(referenceString[0])) {
            return i;  // Page not found in future, replace it
        }
        if (j > farthest) {
            farthest = j;
            index = i;
        }
    }
    return index;
}

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
    int pageFaults = 0;

    // Initialize frames
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = referenceString[i];

        if (!isPresent(frames, page)) {
            if (i < MAX_FRAMES) {
                frames[i] = page;  // Insert page in empty frame
            } else {
                int replaceIndex = findFarthest(frames, MAX_FRAMES, referenceString, i + 1);
                frames[replaceIndex] = page;  // Replace the page that is farthest in the future
            }
            pageFaults++;
        }
    }

    printf("Number of page faults: %d\n", pageFaults);
    return 0;
}
