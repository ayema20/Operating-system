#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void* factorial(void* arg) {
    int n = *(int*)arg;
    long long* result = malloc(sizeof(long long));  
    *result = 1;

    for (int i = 1; i <= n; i++) {
        *result *= i;
    }

    pthread_exit(result);  
}
int main() {
    pthread_t thread;
    int num;
    long long* fact;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (pthread_create(&thread, NULL, factorial, &num) != 0) {
        perror("Failed to create thread");
        return 1;
    }
    pthread_join(thread, (void**)&fact);
    printf("Factorial of %d is: %lld\n", num, *fact);
    printf("Main thread: Work completed.\n");
    free(fact); 
    return 0;
}
