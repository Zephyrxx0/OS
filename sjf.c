#include <stdio.h>

typedef struct {
    int pid;
    int bt;
    int wt;
    int tat;
} Process;

void findWaitingTime(Process proc[], int n) {
    proc[0].wt = 0;
    for (int i = 1; i < n; i++)
        proc[i].wt = proc[i-1].bt + proc[i-1].wt;
}

void findTurnAroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++)
        proc[i].tat = proc[i].bt + proc[i].wt;
}

void findAvgTime(Process proc[], int n) {
    findWaitingTime(proc, n);
    findTurnAroundTime(proc, n);
    printf("\nProcesses\tBurst Time\tWaiting Time\tTurn-Around Time\n");

    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
        printf(" %d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, proc[i].wt, proc[i].tat);
    }

    printf("Average waiting time: %.2f\n", (float)total_wt / n);
    printf("Average turnaround time: %.2f\n", (float)total_tat / n);
}

void ganttChart(Process proc[], int n) {
    findTurnAroundTime(proc, n);
    printf("\nGantt Chart\n");
    printf("-------------------------------------------\n");
    printf("| ");
    for (int i = 0; i < n; i++) {
        printf("P%d | ", proc[i].pid);
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("\t%d", proc[i].tat);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process proc[n];

    printf("\nEnter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Process %d: ", proc[i].pid);
        scanf("%d", &proc[i].bt);
    }

    // Sort processes by burst time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].bt > proc[j+1].bt) {
                Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }

    findAvgTime(proc, n);
    ganttChart(proc, n);

    return 0;
}