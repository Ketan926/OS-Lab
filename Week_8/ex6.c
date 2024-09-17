#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  

int buf[5], f, r;
sem_t mutex, full, empty;
int full_count = 0;
int empty_count = 5;

void print_semaphore_values() 
{
    printf("Semaphore full count: %d\n", full_count);
    printf("Semaphore empty count: %d\n", empty_count);
}

void *produce(void *arg) 
{
    int i;
    for (i = 1; i < 10; i++) 
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        printf("produced item is %d\n", i);
        buf[(++r) % 5] = i;
        sleep(1);
        sem_post(&mutex);
        sem_post(&full);
        full_count++;
        empty_count--;
        print_semaphore_values();  
    }
}

void *consume(void *arg) 
{
    int item, i;
    for (i = 1; i < 10; i++) 
    {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buf[(++f) % 5];
        printf("consumed item is %d\n", item);
        sleep(1);
        sem_post(&mutex);
        sem_post(&empty);
        full_count--;
        empty_count++;
        print_semaphore_values();  
    }
}

int main() 
{
    pthread_t tid1, tid2;
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 5);
    pthread_create(&tid1, NULL, consume, NULL);
    pthread_create(&tid2, NULL, produce, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    return 0;
}
