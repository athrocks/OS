#include <stdio.h>
#include <limits.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime; // Only for preemptive priority scheduling
    int waitingTime;
    int turnaroundTime;
    int finishTime;
};

// Function for Non-Preemptive Priority Scheduling
void priorityNonPreemptive(struct Process proc[], int n) {
    int completed = 0, time = 0, minIndex;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;

    while (completed < n) {
        minIndex = -1;
        int highestPriority = INT_MAX;
        
        // Find the process with the highest priority (lowest priority number) among available processes
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && proc[i].arrivalTime <= time && proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
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

// Function for Preemptive Priority Scheduling
void priorityPreemptive(struct Process proc[], int n) {
    int completed = 0, time = 0, minIndex;
    int highestPriority = INT_MAX;

    while (completed < n) {
        minIndex = -1;
        highestPriority = INT_MAX;

        // Find the process with the highest priority (lowest priority number) among available processes
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= time && proc[i].remainingTime > 0 && proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
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

// Function to display the process information
void displayTimes(struct Process proc[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tFinish Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].processID, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].priority, proc[i].waitingTime, proc[i].turnaroundTime, proc[i].finishTime);
    }
}

// Main function
int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    // Input arrival time, burst time, and priority for each process
    for (int i = 0; i < n; i++) {
        proc[i].processID = i + 1;
        printf("Enter arrival time, burst time, and priority for Process P%d: ", proc[i].processID);
        scanf("%d %d %d", &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
        proc[i].remainingTime = proc[i].burstTime; // For preemptive priority scheduling
    }

    printf("\nChoose Scheduling Type:\n1. Non-Preemptive Priority\n2. Preemptive Priority\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        priorityNonPreemptive(proc, n);
    } else if (choice == 2) {
        priorityPreemptive(proc, n);
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    // Display process information
    displayTimes(proc, n);

    return 0;
}

