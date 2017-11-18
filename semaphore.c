#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 4

int B[N];
int buffer_ptr;
sem_t* elements_sem;
sem_t* spaces_sem;

void *thread_A(void *arg) {    /* producer */
    int i, data;
    for (i = 0; i < 20; i++) {
        data = i;
        sem_wait(spaces_sem);
        B[buffer_ptr++] = data;
        printf("thread_A(): put(%d)\n", data);
        sem_post(elements_sem);
    }
    pthread_exit(0);
}

void *thread_B(void *arg) {    /* consumer */
    int i, data;
    for (i = 0; i < 20; i++) {
        sem_wait(elements_sem);
        data = B[--buffer_ptr];
        printf("thread_B(): get() %d.\n", data);
        sem_post(spaces_sem);
    }
    pthread_exit(0);
}

int main() {
    pthread_t t1;
    pthread_t t2;
    buffer_ptr = 0;

    elements_sem = sem_open("Elements", O_CREAT, 0777, 0);
    spaces_sem = sem_open("Spaces", O_CREAT, 0777, N);
    pthread_setconcurrency(2);
    pthread_create(&t1, NULL, (void *)thread_A, 0);
    pthread_create(&t2, NULL, (void *)thread_B, 0);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}
