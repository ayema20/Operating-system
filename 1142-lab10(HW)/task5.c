#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_STATIONS 2
#define NUM_CARS 6

sem_t wash_stations;
pthread_mutex_t print_mutex;

void* car_thread(void* arg) {
    int car_id = *(int*)arg;
    free(arg);

    printf("Car %d is waiting for a wash station.\n", car_id);
    sem_wait(&wash_stations);

    pthread_mutex_lock(&print_mutex);
    printf("Car %d is being washed.\n", car_id);
    pthread_mutex_unlock(&print_mutex);

    sleep(3); // Each car takes 3 seconds

    pthread_mutex_lock(&print_mutex);
    printf("Car %d finished washing.\n", car_id);
    pthread_mutex_unlock(&print_mutex);
 
    sem_post(&wash_stations);
    pthread_exit(NULL);
}

int main() {
    pthread_t cars[NUM_CARS];

    sem_init(&wash_stations, 0, NUM_STATIONS);
    pthread_mutex_init(&print_mutex, NULL);

    for (int i = 0; i < NUM_CARS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&cars[i], NULL, car_thread, id);
    }

    for (int i = 0; i < NUM_CARS; i++) {
        pthread_join(cars[i], NULL);
    }

    sem_destroy(&wash_stations);
    pthread_mutex_destroy(&print_mutex);

    printf("All cars have been washed.\n");
    return 0;
}
