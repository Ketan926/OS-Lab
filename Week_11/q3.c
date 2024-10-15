#include <stdio.h>
#include <stdlib.h>
#define MAX_REQUESTS 100
struct DSA 
{
    int request_id;
    int arrival_time_stamp;
    int cylinder;
    int address;
    int process_id;
};
void fcfs(struct DSA requests[], int n);
void sstf(struct DSA requests[], int n, int start_cylinder);

int main() 
{
    struct DSA requests[MAX_REQUESTS];
    int n, start_cylinder;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) 
    {
        printf("Enter request ID, arrival time, cylinder, address, process ID for request %d: ", i + 1);
        scanf("%d %d %d %d %d", 
            &requests[i].request_id, 
            &requests[i].arrival_time_stamp, 
            &requests[i].cylinder, 
            &requests[i].address, 
            &requests[i].process_id);
    }
    printf("Enter the starting cylinder for SSTF: ");
    scanf("%d", &start_cylinder);
    printf("\nFCFS Disk Scheduling:\n");
    fcfs(requests, n);
    printf("\nSSTF Disk Scheduling:\n");
    sstf(requests, n, start_cylinder);
    return 0;
}
void fcfs(struct DSA requests[], int n) 
{
    printf("Request Order: ");
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", requests[i].request_id);
    }
    printf("\n");
}
void sstf(struct DSA requests[], int n, int start_cylinder) 
{
    int completed[MAX_REQUESTS] = {0};  
    int current_cylinder = start_cylinder;
    int total_movement = 0;
    int count = 0;
    while (count < n) 
    {
        int closest_index = -1;
        int min_distance = __INT_MAX__;
        for (int i = 0; i < n; i++) 
        {
            if (!completed[i]) 
            {
                int distance = abs(requests[i].cylinder - current_cylinder);
                if (distance < min_distance) 
                {
                    min_distance = distance;
                    closest_index = i;
                }
            }
        }
        if (closest_index != -1) 
        {
            printf("Servicing request ID: %d at cylinder: %d\n", requests[closest_index].request_id, requests[closest_index].cylinder);
            total_movement += min_distance;
            current_cylinder = requests[closest_index].cylinder;
            completed[closest_index] = 1;
            count++;
        }
    }
    printf("Total head movement for SSTF: %d\n", total_movement);
}
