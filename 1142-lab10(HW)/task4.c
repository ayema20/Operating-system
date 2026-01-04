#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_WORKERS 3
#define NUM_TASKS 10

sem_t worker_sem;
pthread_mutex_t print_mutex;

void* task_thread(void* arg) {
    int task_id = *(int*)arg;
    free(arg);

    sem_wait(&worker_sem); // Wait for an available worker

    pthread_mutex_lock(&print_mutex);
    printf("Task %d started by a worker.\n", task_id);
    pthread_mutex_unlock(&print_mutex);

    sleep(rand() % 2 + 1); // Simulate task running 1-2 seconds

    pthread_mutex_lock(&print_mutex);
    printf("Task %d finished.\n", task_id);
    pthread_mutex_unlock(&print_mutex);

    sem_post(&worker_sem); // Worker becomes free
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    pthread_t tasks[NUM_TASKS];

    sem_init(&worker_sem, 0, NUM_WORKERS);
    pthread_mutex_init(&print_mutex, NULL);

    for (int i = 0; i < NUM_TASKS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&tasks[i], NULL, task_thread, id);
    }

    for (int i = 0; i < NUM_TASKS; i++) {
        pthread_join(tasks[i], NULL);
    }

    sem_destroy(&worker_sem);
    pthread_mutex_destroy(&print_mutex);

    printf("All tasks completed.\n");
    return 0;
}
