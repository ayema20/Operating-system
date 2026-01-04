#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_COMPUTERS 4
#define NUM_STUDENTS 8

sem_t computers_sem;
pthread_mutex_t lab_mutex;
int computer_in_use[NUM_COMPUTERS] = {0}; // 0=free, 1=occupied

void* student_thread(void* arg) {
    int student_id = *(int*)arg;
    free(arg);

    printf("Student %d is waiting for a computer.\n", student_id);
    sem_wait(&computers_sem); // Wait for available computer

    pthread_mutex_lock(&lab_mutex);
    int assigned = -1;
    for (int i = 0; i < NUM_COMPUTERS; i++) {
        if (!computer_in_use[i]) {
            computer_in_use[i] = 1;
            assigned = i;
            break;
        }
    }
    printf("Student %d is using computer %d\n", student_id, assigned);
    pthread_mutex_unlock(&lab_mutex);

    sleep(rand() % 3 + 1); // Using computer 1-3 seconds

    pthread_mutex_lock(&lab_mutex);
    computer_in_use[assigned] = 0;
    printf("Student %d left computer %d\n", student_id, assigned);
    pthread_mutex_unlock(&lab_mutex);

    sem_post(&computers_sem); // Free the computer
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    pthread_t students[NUM_STUDENTS];

    sem_init(&computers_sem, 0, NUM_COMPUTERS);
    pthread_mutex_init(&lab_mutex, NULL);

    for (int i = 0; i < NUM_STUDENTS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&students[i], NULL, student_thread, id);
    }

    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(students[i], NULL);
    }

    sem_destroy(&computers_sem);
    pthread_mutex_destroy(&lab_mutex);

    printf("All students finished using the lab.\n");
    return 0;
}
