#include <stdio.h>

typedef struct {
    int pid;        
    int bt;         
    int pri;        
    int wt;         
    int tat;        
} Process;

void sortByPriority(Process proc[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].pri > proc[j].pri) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void calculateTimes(Process proc[], int n) {
    proc[0].wt = 0;  
    proc[0].tat = proc[0].bt;  

    for (int i = 1; i < n; i++) {
        proc[i].wt = proc[i - 1].wt + proc[i - 1].bt; 
        proc[i].tat = proc[i].wt + proc[i].bt;        
    }
}

void displayGanttChart(Process proc[], int n) {
    printf("\nGantt Chart:\n");
    printf("|\t");

    for (int i = 0; i < n; i++) {
        printf("P%d\t|\t", proc[i].pid);
    }
    printf("\n0\t\t");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t", proc[i].tat);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d\n", i + 1);
        proc[i].pid = i + 1;  
        printf("Enter Burst Time: ");
        scanf("%d", &proc[i].bt);
        printf("Enter Priority: ");
        scanf("%d", &proc[i].pri);
    }

    sortByPriority(proc, n);
    
    calculateTimes(proc, n);
    
    displayGanttChart(proc, n);

    printf("\nProcess Table (PID, Burst Time, Priority, Waiting Time, Turnaround Time):\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, proc[i].pri, proc[i].wt, proc[i].tat);
    }

    return 0;
}
