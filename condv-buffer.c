#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 4

int B[N];
int in_ptr, out_ptr;
int count;
pthread_cond_t full, empty;
pthread_mutex_t lock;

void *thread_A(void *arg) {    /* producer */
    int i, data;
    for (i = 0; i < 20; i++) {
        data = i;
        pthread_mutex_lock(&lock);
        while (count >= N) pthread_cond_wait(&full, &lock);
        count++;
        B[in_ptr++] = data;
        printf("thread_A(): put(%d)\n", data);
        if (in_ptr >= N) in_ptr = 0;
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&empty);
    }
    pthread_exit(0);
}

void *thread_B(void *arg) {    /* consumer */
    int i, data;
    for (i = 0; i < 20; i++) {
        sleep(1);
        pthread_mutex_lock(&lock);
        while (count == 0) pthread_cond_wait(&empty, &lock);
        count--;
        data = B[out_ptr++];
        printf("thread_B(): get() %d.\n", data);
        if (out_ptr >= N) out_ptr = 0;
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&full);
    }
    pthread_exit(0);
}

int main() {
    pthread_t t1;
    pthread_t t2;
    in_ptr = 0;
    out_ptr = 0;
    count = 0;
    
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_setconcurrency(2);
    pthread_create(&t1, NULL, (void *)thread_A, 0);
    pthread_create(&t2, NULL, (void *)thread_B, 0);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}
