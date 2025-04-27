#include <stdio.h>
<<<<<<< HEAD
void findWaitingTime(int processes[], int n, int bt[], int wt[]){
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]){
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findAvgTime(int processes[], int n, int bt[]){
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);
    printf("Processes   Burst Time  Waiting Time   Turn-Around Time\n");
    for (int i = 0; i < n; i++){
        total_wt += wt[i];
        total_tat += tat[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    float s = (float)total_wt/(float)n;
    float t = (float)total_tat/(float)n;
    
    printf("Average waiting time: %.2f\n", s);
    printf("Average turnaround time: %.2f\n", t);

}

int main()
{
    int processes[] = { 1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = {10, 5, 8};
    findAvgTime(processes, n, burst_time);
=======

struct Process {
    int pid;
    int bt;
    int wt;
    int tat;
};

void findWaitingTime(struct Process p[], int n) {
    p[0].wt = 0;
    for (int i = 1; i < n; i++)
        p[i].wt = p[i-1].wt + p[i-1].bt;
}

void findTurnAroundTime(struct Process p[], int n) {
    for (int i = 0; i < n; i++)
        p[i].tat = p[i].bt + p[i].wt;
}

void findAvgTime(struct Process p[], int n) {
    findWaitingTime(p, n);
    findTurnAroundTime(p, n);
    int total_wt = 0, total_tat = 0;
    printf("PID\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }
    printf("Average waiting time: %.2f\n", (float)total_wt / n);
    printf("Average turnaround time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].wt = 0;
        p[i].tat = 0;
    }
    findAvgTime(p, n);
>>>>>>> 20035c9 (Initial commit)
    return 0;
}
