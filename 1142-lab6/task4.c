// add two more process in code 4

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_ITERATIONS 1000000

int count = 10;
pthread_mutex_t mutex; // mutex object

// Critical section function
void critical_section(int process) {
    if (process == 0 || process == 2) { // decrement processes
        for (int i = 0; i < NUM_ITERATIONS; i++)
            count--;
    } else { // increment processes
        for (int i = 0; i < NUM_ITERATIONS; i++)
            count++;
    }
}

// Process 0 (decrement)
void *process0(void *arg) {
    pthread_mutex_lock(&mutex);
    critical_section(0);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

// Process 1 (increment)
void *process1(void *arg) {
    pthread_mutex_lock(&mutex);
    critical_section(1);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

// Process 2 (decrement)
void *process2(void *arg) {
 //   pthread_mutex_lock(&mutex);
    critical_section(2);
   // pthread_mutex_unlock(&mutex);
    return NULL;
}

// Process 3 (increment)
void *process3(void *arg) {
    pthread_mutex_lock(&mutex);
    critical_section(3);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t thread0, thread1, thread2, thread3, thread4, thread5;

    pthread_mutex_init(&mutex, NULL); // initialize mutex

    // Create 6 threads (3 decrementers, 3 incrementers)
    pthread_create(&thread0, NULL, process0, NULL);
    pthread_create(&thread1, NULL, process1, NULL);
    pthread_create(&thread2, NULL, process2, NULL);
    pthread_create(&thread3, NULL, process3, NULL);
    pthread_create(&thread4, NULL, process0, NULL); // reuse decrement
    pthread_create(&thread5, NULL, process1, NULL); // reuse increment

    // Wait for all threads to finish
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);

    pthread_mutex_destroy(&mutex); // destroy mutex

    printf("Final count: %d\n", count);

    return 0;
}