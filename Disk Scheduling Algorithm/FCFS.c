#include <stdio.h>
#include <stdlib.h>

void FCFS(int requests[], int n, int head) {
    int seek_time = 0;
    printf("Request\tSeek Sequence\n");
    printf("%d\t%d\n", head, 0);
    
    for (int i = 0; i < n; i++) {
        seek_time += abs(requests[i] - head);
        printf("%d\t%d\n", requests[i], seek_time);
        head = requests[i];
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

    FCFS(requests, n, head);

    return 0;
}
