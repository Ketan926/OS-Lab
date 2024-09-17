#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  

int buf[10], f = 0, r = 0;
sem_t mutex, full, empty;
int items_produced = 0;
int items_consumed = 0;

void print_semaphore_values() 
{
    int full_value, empty_value;
    sem_getvalue(&full, &full_value);
    sem_getvalue(&empty, &empty_value);

    printf("Semaphore full count: %d\n", full_value);
    printf("Semaphore empty count: %d\n", empty_value);
    printf("Items produced: %d\n", items_produced);
    printf("Items consumed: %d\n", items_consumed);
}

void *produce(void *arg) 
{
    int i;
    for (i = 1; i <= 20; i++) 
    {  
        sem_wait(&empty);
        sem_wait(&mutex);
        while (items_produced - items_consumed >= 10) 
        {
            sem_post(&mutex);
            sem_post(&empty); 
            sem_wait(&full); 
            sem_wait(&mutex); 
        }

        printf("produced item is %d\n", i);
        buf[r] = i;
        r = (r + 1) % 10;
        items_produced++;
        sleep(1);
        sem_post(&mutex);
        sem_post(&full);

        print_semaphore_values(); 
    }
    return NULL;
}

void *consume(void *arg) 
{
    int item, i;
    for (i = 1; i <= 20; i++) 
    {  
        sem_wait(&full);
        sem_wait(&mutex);

        item = buf[f];
        f = (f + 1) % 10;
        printf("consumed item is %d\n", item);
        items_consumed++;
        sleep(1);
        sem_post(&mutex);
        sem_post(&empty);

        print_semaphore_values();  
    }
    return NULL;
}

int main() 
{
    pthread_t tid1, tid2;
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);  
    sem_init(&empty, 0, 10); 
    pthread_create(&tid1, NULL, consume, NULL);
    pthread_create(&tid2, NULL, produce, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
