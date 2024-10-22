#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 100
#define FCFS_TIME_QUANTUM 5 // Time quantum for FCFS to switch to the next queue
#define RR_TIME_QUANTUM 2    // Time quantum for Round Robin
#define SJF_THRESHOLD 10      // Time threshold to switch from RR to SJF

typedef struct Process 
{
    int id;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int priority; // 0 = High (FCFS), 1 = Medium (RR), 2 = Low (SJF)
} Process;

typedef struct QueueNode 
{
    Process *process;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue 
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

// Function prototypes
Queue* createQueue();
void enqueue(Queue *q, Process *p);
Process* dequeue(Queue *q);
int isEmpty(Queue *q);
void fcfs(Queue *q, Queue *nextQueue);
void roundRobin(Queue *q, Queue *nextQueue);
void sjf(Queue *q);
void mlfq(Process processes[], int n);

int main() 
{
    Process processes[MAX_PROCESSES];
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) 
    {
        processes[i].id = i + 1;
        printf("Enter burst time and arrival time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].burst_time, &processes[i].arrival_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].priority = 0; 
    }
    mlfq(processes, n);
    return 0;
}

Queue* createQueue() 
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, Process *p) 
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->process = p;
    newNode->next = NULL;
    if (isEmpty(q)) 
    {
        q->front = q->rear = newNode;
    } 
    else 
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

Process* dequeue(Queue *q) 
{
    if (isEmpty(q)) 
        return NULL;
    QueueNode *temp = q->front;
    Process *process = temp->process;
    q->front = q->front->next;
    if (q->front == NULL) 
        q->rear = NULL;
    free(temp);
    return process;
}

int isEmpty(Queue *q) 
{
    return q->front == NULL;
}

void fcfs(Queue *q, Queue *nextQueue) 
{
    int time_elapsed = 0;
    while (!isEmpty(q)) 
    {
        Process *p = dequeue(q);
        if (p->arrival_time > time_elapsed) 
        {
            printf("Time %d: Idle\n", time_elapsed);
            time_elapsed = p->arrival_time;
        }
        int time_to_run = (p->remaining_time > FCFS_TIME_QUANTUM) ? FCFS_TIME_QUANTUM : p->remaining_time;
        printf("Processing P%d (FCFS): %dms\n", p->id, time_to_run);
        p->remaining_time -= time_to_run;
        time_elapsed += time_to_run;
        if (p->remaining_time > 0) 
        {
            printf("P%d not finished, moving to next queue.\n", p->id);
            enqueue(nextQueue, p);
        } 
        else 
        {
            printf("P%d finished execution.\n", p->id);
            free(p);
        }
    }
}

void roundRobin(Queue *q, Queue *nextQueue) 
{
    int total_time = 0; 
    int time_quantum = 0;
    while (!isEmpty(q)) 
    {
        Process *p = dequeue(q);
        if (p->arrival_time > total_time) 
        {
            printf("Time %d: Idle\n", total_time);
            total_time = p->arrival_time;
        }
        int time_to_run = p->remaining_time > RR_TIME_QUANTUM ? RR_TIME_QUANTUM : p->remaining_time;
        printf("Processing P%d (RR): %dms\n", p->id, time_to_run);
        p->remaining_time -= time_to_run;
        total_time += time_to_run;
        if (p->remaining_time > 0) 
        {
            time_quantum += time_to_run;
            if (time_quantum >= SJF_THRESHOLD) 
            {
                p->priority = 2;
                enqueue(nextQueue, p);
            } 
            else 
            {
                enqueue(q, p);
            }
        } 
        else 
        {
            printf("P%d finished execution.\n", p->id);
            free(p);
        }
    }
}

void sjf(Queue *q) 
{
    while (!isEmpty(q)) 
    {
        Process *p = dequeue(q);
        printf("Processing P%d (SJF): %dms\n", p->id, p->remaining_time);
        free(p);
    }
}
void mlfq(Process processes[], int n) 
{
    Queue *queue1 = createQueue(); 
    Queue *queue2 = createQueue(); 
    Queue *queue3 = createQueue(); 
    for (int i = 0; i < n; i++) 
    {
        Process *newProcess = (Process *)malloc(sizeof(Process));
        memcpy(newProcess, &processes[i], sizeof(Process));
        enqueue(queue1, newProcess); 
    }
    printf("\n=== Multilevel Feedback Queue Scheduling ===\n");
    printf("\n=== Queue 1: FCFS ===\n");
    fcfs(queue1,queue2);
    printf("\n=== Queue 2: Round Robin ===\n");
    roundRobin(queue2,queue3);
    printf("\n=== Queue 3: Shortest Job First ===\n");
    sjf(queue3);
    free(queue1);
    free(queue2);
    free(queue3);
}