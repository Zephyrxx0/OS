#include <stdio.h>
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

typedef struct {
    int id;
    int max[MAX_RESOURCES];
    int alloc[MAX_RESOURCES];
    int need[MAX_RESOURCES];
} Process;

int available[MAX_RESOURCES];
int num_processes, num_resources;

void calculateNeed(Process p[]) {
    for (int i = 0; i < num_processes; i++)
        for (int j = 0; j < num_resources; j++)
            p[i].need[j] = p[i].max[j] - p[i].alloc[j];
}

int isSafeState(Process p[]) {
    int work[MAX_RESOURCES], finish[MAX_PROCESSES] = {0}, safeSeq[MAX_PROCESSES], count = 0;
    for (int i = 0; i < num_resources; i++) work[i] = available[i];

    while (count < num_processes) {
        int found = 0;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < num_resources; j++)
                    if (p[i].need[j] > work[j]) break;
                if (j == num_resources) {
                    for (int k = 0; k < num_resources; k++)
                        work[k] += p[i].alloc[k];
                    finish[i] = 1;
                    safeSeq[count++] = p[i].id;
                    found = 1;
                }
            }
        }
        if (!found) return 0;
    }

    printf("System is in a SAFE state.\nSafe Sequence:");
    for (int i = 0; i < num_processes; i++)
        printf(" P%d", safeSeq[i]);
    printf("\n");
    return 1;
}

void requestResources(Process p[]) {
    int pid, req[MAX_RESOURCES];
    printf("\nEnter process id for request: ");
    scanf("%d", &pid);
    printf("Enter requested resources:\n");
    for (int i = 0; i < num_resources; i++)
        scanf("%d", &req[i]);

    int idx = pid - 1;
    for (int j = 0; j < num_resources; j++) {
        if (req[j] > p[idx].need[j] || req[j] > available[j]) {
            printf("Request cannot be granted.\n");
            return;
        }
        available[j] -= req[j];
        p[idx].alloc[j] += req[j];
        p[idx].need[j]  -= req[j];
    }

    if (!isSafeState(p)) {
        printf("Rolling back.\n");
        for (int j = 0; j < num_resources; j++) {
            available[j] += req[j];
            p[idx].alloc[j] -= req[j];
            p[idx].need[j]  += req[j];
        }
    } else {
        printf("Request granted.\n");
    }
}

int main() {
    Process p[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter available resources:\n");
    for (int i = 0; i < num_resources; i++)
        scanf("%d", &available[i]);

    for (int i = 0; i < num_processes; i++) {
        p[i].id = i + 1;
        printf("Process P%d max resources:\n", p[i].id);
        for (int j = 0; j < num_resources; j++)
            scanf("%d", &p[i].max[j]);
        printf("Process P%d allocated resources:\n", p[i].id);
        for (int j = 0; j < num_resources; j++)
            scanf("%d", &p[i].alloc[j]);
    }

    calculateNeed(p);
    if (isSafeState(p))
        requestResources(p);

    return 0;
}
