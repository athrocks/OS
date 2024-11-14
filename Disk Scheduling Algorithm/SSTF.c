#include <stdio.h>
#include <stdlib.h>

void SSTF(int requests[], int n, int head) {
    int seek_time = 0, completed = 0, min_seek, diff, closest_index;
    int processed[n], i;

    for (i = 0; i < n; i++)
        processed[i] = 0;

    printf("Request\tSeek Sequence\n");
    printf("%d\t%d\n", head, 0);

    while (completed < n) {
        min_seek = 100000; // Large number for comparison
        for (i = 0; i < n; i++) {
            if (!processed[i]) {
                diff = abs(requests[i] - head);
                if (diff < min_seek) {
                    min_seek = diff;
                    closest_index = i;
                }
            }
        }

        seek_time += min_seek;
        processed[closest_index] = 1;
        head = requests[closest_index];
        printf("%d\t%d\n", head, seek_time);
        completed++;
    }

    printf("Total Seek Time: %d\n", seek_time);
}

int main() {
    int n, head;
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    SSTF(requests, n, head);

    return 0;
}
