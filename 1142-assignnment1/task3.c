#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* number_info(void* arg) {
    int num = *(int*)arg;  
    int square = num * num;
    int cube = num * num * num;

    printf("Thread: Number = %d\n", num);
    printf("Thread: Square = %d\n", square);
    printf("Thread: Cube   = %d\n", cube);

    return NULL;
}

int main() {
    pthread_t thread;
    int number;

    printf("Enter an integer: ");
    scanf("%d", &number);

    if (pthread_create(&thread, NULL, number_info, &number) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    printf("Main thread: Waiting for computation...\n");

    pthread_join(thread, NULL);

    printf("Main thread: Work completed.\n");
    return 0;
}
