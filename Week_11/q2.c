#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n; 
int m; 
int allocated[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
pthread_mutex_t lock;

int bankers_algorithm(int process_index, int request[]) 
{
    for (int j = 0; j < m; j++) 
    {
        if (request[j] > need[process_index][j] || request[j] > available[j])
        {
            return 0; 
        }
    }
    for (int j = 0; j < m; j++) 
    {
        available[j] -= request[j];
        allocated[process_index][j] += request[j];
        need[process_index][j] -= request[j];
    }
    int work[MAX_RESOURCES];
    for (int j = 0; j < m; j++) 
    {
        work[j] = available[j];
    }
    int finish[MAX_PROCESSES] = {0};
    int safe_sequence[MAX_PROCESSES];
    int count = 0;
    while (count < n) 
    {
        int found = 0;
        for (int i = 0; i < n; i++) 
        {
            if (!finish[i]) 
            {
                int j;
                for (j = 0; j < m; j++) 
                {
                    if (need[i][j] > work[j]) 
                    {
                        break;
                    }
                }
                if (j == m) 
                { 
                    for (int k = 0; k < m; k++) 
                    {
                        work[k] += allocated[i][k];
                    }
                    safe_sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) 
        {
            break; 
        }
    }
    if (count < n) 
    {
        for (int j = 0; j < m; j++) 
        {
            available[j] += request[j];
            allocated[process_index][j] -= request[j];
            need[process_index][j] += request[j];
        }
        return 0; 
    }
    printf("Safe sequence: ");
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");

    return 1;
}
void release_resources(int process_index) 
{
    for (int j = 0; j < m; j++) 
    {
        available[j] += allocated[process_index][j];
        allocated[process_index][j] = 0; 
        need[process_index][j] = max[process_index][j]; 
    }
}
void *request_resources(void *arg) 
{
    int process_index = (int)(long)arg;
    int request[MAX_RESOURCES];
    for (int j = 0; j < m; j++) 
    {
        request[j] = rand() % (need[process_index][j] + 1);
    }
    pthread_mutex_lock(&lock);
    if (bankers_algorithm(process_index, request)) 
    {
        printf("Process %d: Resources granted: ", process_index);
        for (int j = 0; j < m; j++) 
        {
            printf("%d ", request[j]);
        }
        printf("\n");
        release_resources(process_index);
    } 
    else 
    {
        printf("Process %d: Resources denied: ", process_index);
        for (int j = 0; j < m; j++) 
        {
            printf("%d ", request[j]);
        }
        printf("\n");
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() 
{
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    printf("Enter maximum resources for each process:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) 
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) 
        {
            scanf("%d", &allocated[i][j]);
        }
    }
    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++) 
    {
        scanf("%d", &available[i]);
    }
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
    pthread_t threads[n];
    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < n; i++) 
    {
        pthread_create(&threads[i], NULL, request_resources, (void *)(long)i);
    }
    for (int i = 0; i < n; i++) 
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}

