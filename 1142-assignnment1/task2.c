#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* greet(void* arg) {
    char* name = (char*)arg;  // get name passed from main
    printf("Hello, %s! Welcome to multithreading!\n", name);
    return NULL;
}

int main() {
    pthread_t thread;
    char name[50];

    printf("Enter your name: ");
    scanf("%s", name);

    // Create thread and pass name as argument
    if (pthread_create(&thread, NULL, greet, name) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    printf("Main thread: Waiting for greeting...\n");

    // Wait for the greeting thread to finish
    pthread_join(thread, NULL);

    printf("Main thread: Greeting completed!\n");
    return 0;
}
