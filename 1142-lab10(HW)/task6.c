#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CARS_ON_BRIDGE 3
#define TOTAL_CARS 8

sem_t bridge_sem;
pthread_mutex_t print_mutex;

void* car_thread(void* arg) {
    int car_id = *(int*)arg;
    free(arg);

    printf("Car %d is waiting to enter the bridge.\n", car_id);
    sem_wait(&bridge_sem);

    pthread_mutex_lock(&print_mutex);
    printf("Car %d is on the bridge.\n", car_id);
    pthread_mutex_unlock(&print_mutex);

    sleep(rand() % 3 + 1); // Random crossing time 1-3 sec

    pthread_mutex_lock(&print_mutex);
    printf("Car %d has left the bridge.\n", car_id);
    pthread_mutex_unlock(&print_mutex);

    sem_post(&bridge_sem);
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    pthread_t cars[TOTAL_CARS];

    sem_init(&bridge_sem, 0, MAX_CARS_ON_BRIDGE);
    pthread_mutex_init(&print_mutex, NULL);

    for (int i = 0; i < TOTAL_CARS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&cars[i], NULL, car_thread, id);
    }

    for (int i = 0; i < TOTAL_CARS; i++) {
        pthread_join(cars[i], NULL);
    }

    sem_destroy(&bridge_sem);
    pthread_mutex_destroy(&print_mutex);

    printf("All cars have crossed the bridge.\n");
    return 0;
}
