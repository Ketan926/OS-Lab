#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  
// Shared resources
int read_count = 0;  // Number of readers currently reading
sem_t mutex;         // Mutex for protecting the read_count
sem_t write_lock;    // Semaphore to lock the writer

void *reader(void *arg) 
{
    int id = *((int *)arg);
    while (1) 
    {
        sem_wait(&mutex); 
        read_count++;
        if (read_count == 1) 
        {
            sem_wait(&write_lock); 
        }
        sem_post(&mutex); 
        printf("Reader %d is reading\n", id);
        sleep(1);
        sem_wait(&mutex); 
        read_count--;
        if (read_count == 0) 
        {
            sem_post(&write_lock); 
        }
        sem_post(&mutex);  
        sleep(1);  
    }
    return NULL;
}

void *writer(void *arg) 
{
    int id = *((int *)arg);
    while (1) 
    {
        sem_wait(&write_lock);  
        printf("Writer %d is writing\n", id);
        sleep(1);  
        sem_post(&write_lock);  
        sleep(1); 
    }
    return NULL;
}
int main() 
{
    pthread_t readers[5], writers[2];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[2] = {1, 2};
    sem_init(&mutex, 0, 1);       
    sem_init(&write_lock, 0, 1);  
    for (int i = 0; i < 5; i++) 
    {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    for (int i = 0; i < 2; i++) 
    {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    for (int i = 0; i < 5; i++) 
    {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) 
    {
        pthread_join(writers[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}
