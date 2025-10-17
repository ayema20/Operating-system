#include <stdio.h>
#include <pthread.h>
typedef struct {
    char* message;
    float value;
} ThreadData;
void* printData(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    printf("%s\n", data->message);
    printf("%.2f\n", data->value);
    return NULL;
}
int main() {
    pthread_t t1;
    ThreadData data1 = {"Ayema", 3.31};
    pthread_create(&t1, NULL, printData, &data1);
    pthread_join(t1, NULL);
    return 0;
}
