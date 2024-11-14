#include <stdio.h>
#include <stdlib.h>

void SCAN(int requests[], int n, int head, int disk_size) {
    int seek_time = 0, i, j;
    requests[n] = 0;
    requests[n + 1] = disk_size - 1;
    n += 2;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    int pos = 0;
    while (pos < n && requests[pos] < head)
        pos++;

    printf("Request\tSeek Sequence\n");
    printf("%d\t%d\n", head, 0);

    for (i = pos; i < n; i++) {
        seek_time += abs(requests[i] - head);
        printf("%d\t%d\n", requests[i], seek_time);
        head = requests[i];
    }

    for (i = pos - 1; i >= 0; i--) {
        seek_time += abs(requests[i] - head);
        printf("%d\t%d\n", requests[i], seek_time);
        head = requests[i];
    }

    printf("Total Seek Time: %d\n", seek_time);
}

int main() {
    int n, head, disk_size;
    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int requests[n + 2];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    SCAN(requests, n, head, disk_size);

    return 0;
}
