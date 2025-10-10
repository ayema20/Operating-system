 #include <stdio.h>
 #include <pthread.h>
 void* print_number(void* arg) {
 int num = *(int*)arg;
 printf("Thread received number: %d\n", num);
 printf("Square: %d\n", num * num);
 return NULL;}
 int main() {
 pthread_t thread_id;
 int number = 42;
 printf("Creating thread with argument: %d\n", number);
 pthread_create(&thread_id, NULL, print_number, &number);
 pthread_join(thread_id, NULL);
 printf("Main thread done.\n");
 return 0;
 }