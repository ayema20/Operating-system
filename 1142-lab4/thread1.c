 #include <stdio.h>
 #include <pthread.h>
 #include <unistd.h>
 void* thread_function(void* arg) {
 printf("Hello from the new thread!\n");
 printf("Thread ID: %lu\n", pthread_self());
 return NULL;}
 int main() {
 pthread_t thread_id;
 printf("Main thread starting...\n");
 printf("Main Thread ID: %lu\n", pthread_self());
 pthread_create(&thread_id, NULL, thread_function, NULL);
 pthread_join(thread_id, NULL);
 printf("Main thread exiting...\n");
 return 0;
 }
