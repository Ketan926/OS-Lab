#include <stdlib.h>
#include <stdio.h>


int bankers(int n, int m, int done[n], int allocated[n][m], int max[n][m], int need[n][m], int avl[m]) 
{
    int i, j, k;
    int flag;
    for (i = 0; i < n; i++) 
    {
        flag = 1;
        for (j = 0; j < m; j++) 
        {
            if (need[i][j] > avl[j]) 
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1 && done[i] != 1) 
        {
            done[i] = 1;
            for (k = 0; k < m; k++) 
            {
                avl[k] += allocated[i][k];
                allocated[i][k] = 0;
            }
            return i;
        }
    }
    return -1; // No process can proceed
}

int can_grant_request(int n, int m, int allocated[n][m], int max[n][m], int need[n][m], int avl[m], int process_index, int request[m]) 
{
    int safeseq[n]={0};
    for (int j = 0; j < m; j++) 
    {
        if (request[j] > need[process_index][j] || request[j] > avl[j]) 
        {
            return 0; 
        }
    }
    for (int j = 0; j < m; j++) 
    {
        avl[j] -= request[j];
        allocated[process_index][j] += request[j];
        need[process_index][j] -= request[j];
    }
    int done[n];
    for (int i = 0; i < n; i++) done[i] = 0;
    int safe_count = 0;
    while (safe_count < n) 
    {
        int ind = bankers(n, m, done, allocated, max, need, avl);
        if (ind == -1) 
        {
            for (int j = 0; j < m; j++) 
            {
                avl[j] += request[j];
                allocated[process_index][j] -= request[j];
                need[process_index][j] += request[j];
            }
            return 0;
        }
        safeseq[safe_count]=ind;
        safe_count++;
    }
    printf("Safe sequence is:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", safeseq[i]);
    }
    printf("\n");
    return 1;
}

int main() 
{
    int m, n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int pro[n], res[m], done[n], safe[n], avl[m], given[m];
    printf("Enter number of resources of each type: ");
    for (int i = 0; i < m; i++) 
    {
        scanf("%d", &res[i]);
        given[i] = avl[i] = 0;
    }

    int max[n][m], allocated[n][m], need[n][m];
    printf("Enter max needs:\n");
    for (int i = 0; i < n; i++) 
    {
        done[i] = 0;
        printf("Enter resources for process %d: ", i + 1);
        for (int j = 0; j < m; j++) 
        {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("Enter allocated resources:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("Enter resources for process %d: ", i + 1);
        for (int j = 0; j < m; j++) 
        {
            scanf("%d", &allocated[i][j]);
            given[j] += allocated[i][j];
        }
    }

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    for (int i = 0; i < m; i++) 
    {
        avl[i] = res[i] - given[i];
    }

    printf("Performing Banker's Algorithm...\n");
    for (int i = 0; i < n; i++) 
    {
        int ind = bankers(n, m, done, allocated, max, need, avl);
        if (ind == -1) 
        {
            printf("Not possible anymore\n");
            break;
        } 
        else 
        {
            safe[i] = ind;
        }
    }

    printf("Need matrix is:\n");
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    printf("Safe sequence is:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", safe[i]);
    }
    printf("\n");

    // Handle requests
    int req[m];
    printf("enter request for process 1\n");
    for(int i=0;i<m;i++)
        scanf("%d",&req[i]);
    printf("\nHandling request from process P1\n");
    for(int i=0;i<m;i++)
        printf("%d ",req[i]);
    printf("\n");
    if (can_grant_request(n, m, allocated, max, need, avl, 1, req)) 
    {
        printf("Request can be granted.\n");
    } 
    else 
    {
        printf("Request cannot be granted.\n");
    }

    printf("enter request for process 4\n");
    for(int i=0;i<m;i++)
        scanf("%d",&req[i]);
    printf("\nHandling request from process P4\n");
    for(int i=0;i<m;i++)
        printf("%d ",req[i]);
    printf("\n");
    if (can_grant_request(n, m, allocated, max, need, avl, 3, req)) 
    {
        printf("Request can be granted.\n");
    } 
    else 
    {
        printf("Request cannot be granted.\n");
    }

    printf("enter request for process 0\n");
    for(int i=0;i<m;i++)
        scanf("%d",&req[i]);
    printf("\nHandling request from process P0\n");
    for(int i=0;i<m;i++)
        printf("%d ",req[i]);
    printf("\n");
    if (can_grant_request(n, m, allocated, max, need, avl, 0, req)) 
    {
        printf("Request can be granted.\n");
    } 
    else 
    {
        printf("Request cannot be granted.\n");
    }
    return 0;
}
