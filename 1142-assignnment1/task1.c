#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* work(void* arg) {
    int num = *(int*)arg;

    printf("Thread %d started. ID = %lu\n", num, pthread_self());

    int t = (rand() % 3) + 1;  // random 1–3 seconds
    sleep(t);

    printf("Thread %d finished after %d seconds.\n", num, t);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int nums[5];
    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        nums[i] = i + 1;
        pthread_create(&threads[i], NULL, work, &nums[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads done!\n");
    return 0;
}
