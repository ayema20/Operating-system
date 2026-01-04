#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  // for sleep
#include <time.h>

#define N 5          // Number of rooms
#define TOTAL_PEOPLE 10  // Total number of people trying to enter

sem_t rooms_semaphore;      // Counting semaphore for rooms
int current_occupancy = 0;  // Track occupancy
pthread_mutex_t occupancy_mutex; // Mutex to safely update occupancy

void* person_thread(void* arg) {
    int person_id = *(int*)arg;
    free(arg); // Free dynamically allocated memory

    printf("Person %d is waiting to enter.\n", person_id);

    // Wait for a room
    sem_wait(&rooms_semaphore);

    // Update occupancy
    pthread_mutex_lock(&occupancy_mutex);
    current_occupancy++;
    printf("Person %d entered. Current occupancy: %d/%d\n", person_id, current_occupancy, N);
    pthread_mutex_unlock(&occupancy_mutex);

    // Stay for 1-3 seconds
    int stay_time = (rand() % 3) + 1;
    sleep(stay_time);

    // Leave room
    pthread_mutex_lock(&occupancy_mutex);
    current_occupancy--;
    printf("Person %d left. Current occupancy: %d/%d\n", person_id, current_occupancy, N);
    pthread_mutex_unlock(&occupancy_mutex);

    // Release the room
    sem_post(&rooms_semaphore);

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL)); // Seed random number generator

    pthread_t threads[TOTAL_PEOPLE];
    sem_init(&rooms_semaphore, 0, N); // Initialize semaphore with N rooms
    pthread_mutex_init(&occupancy_mutex, NULL);

    // Create threads for each person
    for (int i = 0; i < TOTAL_PEOPLE; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&threads[i], NULL, person_thread, id);
    }

    // Wait for all threads to finish
    for (int i = 0; i < TOTAL_PEOPLE; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    sem_destroy(&rooms_semaphore);
    pthread_mutex_destroy(&occupancy_mutex);

    printf("All people have finished their stay.\n");
    return 0;
}
