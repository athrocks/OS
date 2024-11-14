#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int alloc[MAX][MAX], request[MAX][MAX];
int avail[MAX];
int n, m;

void input() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter request matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);
}

void deadlockDetection() {
    bool finish[MAX] = {false};
    int work[MAX];

    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    int deadlockProcesses[MAX], deadlockCount = 0;

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < n; j++) {
            if (!finish[j]) {
                int k;
                for (k = 0; k < m; k++)
                    if (request[j][k] > work[k])
                        break;

                if (k == m) {
                    for (int l = 0; l < m; l++)
                        work[l] += alloc[j][l];
                    finish[j] = true;
                    found = true;
                }
            }
        }
        if (!found)
            break;
    }

    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlockProcesses[deadlockCount++] = i;
        }
    }

    if (deadlockCount == 0)
        printf("No deadlock detected.\n");
    else {
        printf("Deadlock detected! The following processes are in deadlock:\n");
        for (int i = 0; i < deadlockCount; i++)
            printf("Process %d\n", deadlockProcesses[i]);
    }
}

int main() {
    input();
    deadlockDetection();
    return 0;
}

