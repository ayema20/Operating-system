#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t m;

void* producer(void* a) {
    int id = *(int*)a;

    for(int i = 0; i < 3; i++) {
        int item = id * 10 + i;

        sem_wait(&empty);
        pthread_mutex_lock(&m);

        buffer[in] = item;
        printf("Producer %d produced %d\n", id, item);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&m);
        sem_post(&full);

        sleep(1);
    }
    return NULL;
}

void* consumer(void* a) {
    int id = *(int*)a;

    for(int i = 0; i < 3; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&m);

        int item = buffer[out];
        printf("Consumer %d consumed %d\n", id, item);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&m);
        sem_post(&empty);

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t p[2], c[2];
    int id[2] = {1, 2};

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&m, NULL);

    for(int i = 0; i < 2; i++) {
        pthread_create(&p[i], NULL, producer, &id[i]);
        pthread_create(&c[i], NULL, consumer, &id[i]);
    }

    for(int i = 0; i < 2; i++) {
        pthread_join(p[i], NULL);
        pthread_join(c[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&m);

    return 0;
}
