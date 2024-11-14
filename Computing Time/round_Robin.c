#include <stdio.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime; // Remaining time for each process
    int waitingTime;
    int turnaroundTime;
    int finishTime;
};

// Function to implement Round Robin Scheduling
void roundRobin(struct Process proc[], int n, int quantum) {
    int time = 0; // Current time
    int completed = 0; // Number of completed processes
    int i = 0;

    while (completed < n) {
        // Check if the process is available and has remaining time
        if (proc[i].remainingTime > 0 && proc[i].arrivalTime <= time) {
            if (proc[i].remainingTime > quantum) {
                // Process can only run for the time quantum
                time += quantum;
                proc[i].remainingTime -= quantum;
            } else {
                // Process can finish within the time quantum
                time += proc[i].remainingTime;
                proc[i].finishTime = time;
                proc[i].turnaroundTime = proc[i].finishTime - proc[i].arrivalTime;
                proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
                proc[i].remainingTime = 0;
                completed++;
            }
        }
        // Move to the next process in a cyclic manner
        i = (i + 1) % n;

        // If no process is available at current time, increment time
        if (i == 0 && completed < n) {
            int allRemaining = 1;
            for (int j = 0; j < n; j++) {
                if (proc[j].remainingTime > 0 && proc[j].arrivalTime <= time) {
                    allRemaining = 0;
                    break;
                }
            }
            if (allRemaining) time++;
        }
    }
}

// Function to display the process information
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
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        proc[i].processID = i + 1;
        printf("Enter arrival time and burst time for Process P%d: ", proc[i].processID);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime; // Initialize remaining time
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Call round robin scheduling function
    roundRobin(proc, n, quantum);

    // Display process information
    displayTimes(proc, n);

    return 0;
}

