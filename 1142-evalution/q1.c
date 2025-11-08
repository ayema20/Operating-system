// Write a C program that demonstrates and fixes a race condition:
// 1.  Create a shared global variable                   initialized to 0
// 2.  Create 3 threads, each thread increments
// 3.  First version WITHOUT mutex:
// Create and run the 3 threads
// 1000 times in a loop
// Print the final counter value
// Run multiple times and observe inconsistent results
// 4.  Second version WITH mutex:
// Use mutex to protect the counter increment   Create and run the 3 threads
// Print the final counter value (should always be 3000) 
// Requirements:
// Show both versions (with and without mutex) Add comments explaining why mutex is needed Properly initialize and destroy mutex
#include <stdio.h>
#include <pthread.h>

int counter =0;
pthread_mutex_t lock;

void* increment_without_mutex(void* arg){
    for(int i=0 ; i<1000; i++){
       counter++;}
       return NULL;
}

void* increment_with_mutex(void* arg){
    for(int i=0 ;i<1000;i++){
        pthread_mutex_lock(&lock);
        counter++;
         pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(){
    pthread_t t1,t2,t3;
    counter =0;
    pthread_create(&t1 ,NULL, increment_without_mutex,NULL);
    pthread_create(&t2 ,NULL, increment_without_mutex,NULL);
pthread_create(&t3 ,NULL, increment_without_mutex,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    printf("Without mutex: counter= %d\n",counter);

    counter=0;
    pthread_mutex_init(&lock,NULL);
     pthread_create(&t1 ,NULL, increment_with_mutex,NULL);
      pthread_create(&t2 ,NULL, increment_with_mutex,NULL);
       pthread_create(&t3 ,NULL, increment_with_mutex,NULL);
       pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    printf("With mutex: counter= %d\n",counter);
    pthread_mutex_destroy(&lock);
    return 0;
}

// the mutex will be perfectly inialize using  pthread_mutex_init(&lock,NULL) before any thread uses it
//After finish work it will use this  pthread_mutex_destroy(&lock) to destory mutex