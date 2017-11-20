#include <stdio.h>
#include <pthread.h>

void *thread_A(void *arg) {
    for (;;) printf("Thread A\n");
    pthread_exit(0);
}

void *thread_B(void *arg) {
    for (;;) printf("Thread B\n");
    pthread_exit(0);
}

int main() {
    pthread_t t1;
    pthread_t t2;
    
    pthread_create(&t1, NULL, (void *)thread_A, 0);
    pthread_create(&t2, NULL, (void *)thread_B, 0);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}
