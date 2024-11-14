#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
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

    printf("Enter max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

bool isSafe() {
    int work[MAX];
    bool finish[MAX] = {false};

    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;
                
                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found)
            return false;
    }
    return true;
}

int main() {
    input();
    if (isSafe())
        printf("System is in a safe state.\n");
    else
        printf("System is not in a safe state.\n");
    return 0;
}

