#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;
void* check_student(void* arg) {
    Student* s = (Student*)arg;
    printf("\nStudent ID: %d\n", s->student_id);
    printf("Name: %s\n", s->name);
    printf("GPA: %.2f\n", s->gpa);

    int* is_deans_list = malloc(sizeof(int));
    if (s->gpa >= 3.5) {
        printf("Status: Dean’s List ✅\n");
        *is_deans_list = 1;
    } else {
        printf("Status: Not Eligible ❌\n");
        *is_deans_list = 0;
    }
    pthread_exit(is_deans_list);
}
int main() {
    pthread_t threads[3];
    Student students[3] = {
        {101, "Ali", 3.8},
        {102, "Sara", 3.2},
        {103, "Ahmed", 3.6}
    };

    int* result;
    int total_deans = 0;
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, check_student, &students[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], (void**)&result);
        total_deans += *result;
        free(result);
    }
    printf("\nTotal students on Dean’s List: %d\n", total_deans);
    printf("Main thread: Work completed.\n");
    return 0;
}
