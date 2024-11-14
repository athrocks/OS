#include <stdio.h>

// Structure to store process details
struct Process {
    int processID;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int finishTime;
};

// Function to calculate waiting time, turnaround time, and finish time
void calculateTimes(struct Process proc[], int n) {
    // Calculate waiting time and finish time for each process
    proc[0].waitingTime = 0;  // First process has no waiting time
    proc[0].finishTime = proc[0].burstTime;

    for (int i = 1; i < n; i++) {
        // Waiting time of current process = finish time of previous process
        proc[i].waitingTime = proc[i - 1].finishTime;
        // Finish time = waiting time + burst time of current process
        proc[i].finishTime = proc[i].waitingTime + proc[i].burstTime;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        proc[i].turnaroundTime = proc[i].finishTime;
    }
}

// Function to display the times for each process
void displayTimes(struct Process proc[], int n) {
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\tFinish Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].processID, proc[i].burstTime, proc[i].waitingTime,
               proc[i].turnaroundTime, proc[i].finishTime);
    }
}

// Main function
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input burst time for each process
    for (int i = 0; i < n; i++) {
        proc[i].processID = i + 1;
        printf("Enter burst time for Process P%d: ", proc[i].processID);
        scanf("%d", &proc[i].burstTime);
    }

    // Calculate times
    calculateTimes(proc, n);

    // Display process times
    displayTimes(proc, n);

    return 0;
}

