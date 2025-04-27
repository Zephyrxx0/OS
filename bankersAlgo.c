#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES], allocation[MAX_PROCESSES][MAX_RESOURCES], need[MAX_PROCESSES][MAX_RESOURCES];
int num_processes, num_resources;

void calculateNeed() {
    for (int i = 0; i < num_processes; i++)
        for (int j = 0; j < num_resources; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

int isSafeState() {
    int work[MAX_RESOURCES], finish[MAX_PROCESSES] = {0};
    for (int i = 0; i < num_resources; i++)
        work[i] = available[i];

    int safeSequence[MAX_PROCESSES], count = 0;

    while (count < num_processes) {
        int found = 0;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < num_resources; j++)
                    if (need[i][j] > work[j])
                        break;
                
                if (j == num_resources) {  
                    for (int k = 0; k < num_resources; k++)
                        work[k] += allocation[i][k];
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is in an UNSAFE state!\n");
            return 0;
        }
    }

    printf("System is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < num_processes; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");
    return 1;
}

void requestResources(int process, int request[]) {
    for (int i = 0; i < num_resources; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process P%d is requesting more than its declared maximum.\n", process);
            return;
        }
        if (request[i] > available[i]) {
            printf("Process P%d must wait, not enough resources available.\n", process);
            return;
        }
    }

    for (int i = 0; i < num_resources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (!isSafeState()) {
        printf("Request cannot be granted as it leads to an unsafe state.\n");
        for (int i = 0; i < num_resources; i++) { 
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    } else {
        printf("Request granted.\n");
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter available resources: ");
    for (int i = 0; i < num_resources; i++)
        scanf("%d", &available[i]);

    printf("Enter maximum resources required by each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < num_resources; j++)
            scanf("%d", &max[i][j]);
    }

    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < num_resources; j++)
            scanf("%d", &allocation[i][j]);
    }

    calculateNeed();

    if (isSafeState()) {
        int process, request[MAX_RESOURCES];
        printf("\nEnter process number to request resources: ");
        scanf("%d", &process);
        printf("Enter requested resources: ");
        for (int i = 0; i < num_resources; i++)
            scanf("%d", &request[i]);

        requestResources(process, request);
    }

    return 0;
}
