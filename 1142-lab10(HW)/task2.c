#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // for sleep
#include <time.h>

#define MAX_CONCURRENT_DOWNLOADS 3
#define TOTAL_DOWNLOADS 8

sem_t download_semaphore;       // Counting semaphore
pthread_mutex_t print_mutex;    // Mutex to safely print messages

void* download_thread(void* arg) {
    int file_id = *(int*)arg;
    free(arg); // free allocated memory

    // Wait for a free slot to download
    sem_wait(&download_semaphore);

    // Print start message
    pthread_mutex_lock(&print_mutex);
    printf("Download %d started.\n", file_id);
    pthread_mutex_unlock(&print_mutex);

    // Simulate download (1-5 seconds)
    int download_time = (rand() % 5) + 1;
    sleep(download_time);

    // Print end message
    pthread_mutex_lock(&print_mutex);
    printf("Download %d finished. (Took %d seconds)\n", file_id, download_time);
    pthread_mutex_unlock(&print_mutex);

    // Release semaphore slot
    sem_post(&download_semaphore);

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL)); // Seed for random times

    pthread_t threads[TOTAL_DOWNLOADS];

    // Initialize semaphore with 3 slots
    sem_init(&download_semaphore, 0, MAX_CONCURRENT_DOWNLOADS);
    pthread_mutex_init(&print_mutex, NULL);

    // Create download threads
    for (int i = 0; i < TOTAL_DOWNLOADS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&threads[i], NULL, download_thread, id);
    }

    // Wait for all threads to finish
    for (int i = 0; i < TOTAL_DOWNLOADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    sem_destroy(&download_semaphore);
    pthread_mutex_destroy(&print_mutex);

    printf("All downloads completed.\n");
    return 0;
}
