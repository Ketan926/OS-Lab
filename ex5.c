#include <pthread.h>
#include <stdio.h>

#define NUM_ITERATIONS 10

pthread_mutex_t mutex;
volatile int counter = 0;
volatile int turn = 0; // Shared variable to indicate the turn of the threads

// Thread function
void* count(void* param) {
    int thread_num = *(int*)param; // Determine the thread number (0 or 1)

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);  // Lock the mutex

        // Wait for the turn to be this thread's
        while (turn != thread_num) {
            pthread_mutex_unlock(&mutex); // Unlock while waiting
            pthread_mutex_lock(&mutex);   // Re-lock before checking again
        }

        // Perform counting
        pthread_t thread_id = pthread_self();
        counter++;
        int x = (unsigned long)thread_id % 1000;
        printf("Count = %d\tThread ID: %d\n", counter, x);

        // Switch turn to the other thread
        turn = 1 - thread_num;

        pthread_mutex_unlock(&mutex);  // Unlock the mutex
    }

    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int thread1_num = 0, thread2_num = 1;

    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Failed to initialize mutex");
        return 1;
    }

    // Create two threads
    if (pthread_create(&thread1, NULL, count, &thread1_num) != 0) {
        perror("Failed to create thread1");
        pthread_mutex_destroy(&mutex);
        return 1;
    }

    if (pthread_create(&thread2, NULL, count, &thread2_num) != 0) {
        perror("Failed to create thread2");
        pthread_mutex_destroy(&mutex);
        return 1;
    }

    // Wait for both threads to finish
    if (pthread_join(thread1, NULL) != 0) {
        perror("Failed to join thread1");
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join thread2");
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
