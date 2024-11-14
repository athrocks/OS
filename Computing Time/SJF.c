#include <stdio.h>
#include <limits.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime; // Only used for preemptive SJF
    int waitingTime;
    int turnaroundTime;
    int finishTime;
};

// Function for Non-Preemptive SJF
void sjfNonPreemptive(struct Process proc[], int n) {
    int completed = 0, time = 0, minIndex;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;

    while (completed < n) {
        minIndex = -1;
        int minBurst = INT_MAX;
        
        // Find process with shortest burst time among available processes
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && proc[i].arrivalTime <= time && proc[i].burstTime < minBurst) {
                minBurst = proc[i].burstTime;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            time++;
        } else {
            time += proc[minIndex].burstTime;
            proc[minIndex].finishTime = time;
            proc[minIndex].turnaroundTime = proc[minIndex].finishTime - proc[minIndex].arrivalTime;
            proc[minIndex].waitingTime = proc[minIndex].turnaroundTime - proc[minIndex].burstTime;
            isCompleted[minIndex] = 1;
            completed++;
        }
    }
}

// Function for Preemptive SJF
void sjfPreemptive(struct Process proc[], int n) {
    int completed = 0, time = 0, minIndex;
    int minRemaining = INT_MAX;

    while (completed < n) {
        minIndex = -1;
        minRemaining = INT_MAX;

        // Find process with shortest remaining time among available processes
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= time && proc[i].remainingTime > 0 && proc[i].remainingTime < minRemaining) {
                minRemaining = proc[i].remainingTime;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            time++;
        } else {
            proc[minIndex].remainingTime--;
            time++;

            if (proc[minIndex].remainingTime == 0) {
                proc[minIndex].finishTime = time;
                proc[minIndex].turnaroundTime = proc[minIndex].finishTime - proc[minIndex].arrivalTime;
                proc[minIndex].waitingTime = proc[minIndex].turnaroundTime - proc[minIndex].burstTime;
                completed++;
            }
        }
    }
}

// Function to display process information
void displayTimes(struct Process proc[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tFinish Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].processID, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].waitingTime, proc[i].turnaroundTime, proc[i].finishTime);
    }
}

// Main function
int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    // Input arrival and burst time for each process
    for (int i = 0; i < n; i++) {
        proc[i].processID = i + 1;
        printf("Enter arrival time and burst time for Process P%d: ", proc[i].processID);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime; // For preemptive SJF
    }

    printf("\nChoose Scheduling Type:\n1. Non-Preemptive SJF\n2. Preemptive SJF\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        sjfNonPreemptive(proc, n);
    } else if (choice == 2) {
        sjfPreemptive(proc, n);
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    // Display process information
    displayTimes(proc, n);

    return 0;
}

