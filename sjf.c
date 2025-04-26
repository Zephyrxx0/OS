#include <stdio.h>
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
    int wt[n], tat[n],total_wt = 0, total_tat = 0;;
    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);
    printf("\nProcesses\tBurst Time\tWaiting Time\tTurn-Around Time\n");

    
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
void ganttChart(int processes[], int n, int bt[], int wt[]){
    int tat[n];
    findTurnAroundTime(processes, n, bt, wt, tat);
    printf("\nGantt Chart\n");
    printf("-------------------------------------------\n");
    printf("| ");
    for (int i = 0; i < n; i++){
        printf("P%d | ", processes[i]);
    }
    printf("\n");
    printf("0");
    for (int i = 0; i < n; i++){
        printf("\t%d", tat[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[n], bt[n];
    printf("\nEnter burst time for each process:\n");
    for (int i = 0; i < n; i++){
        processes[i] = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++ ){
            if (bt[j]>bt[j+1]){
                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
                int tempProc = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = tempProc;
            }
        }
    }

    findAvgTime(processes, n , bt);
    ganttChart(processes, n, bt, bt);
    return 0;
}