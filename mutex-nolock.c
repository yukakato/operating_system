#include <stdio.h>
#include <pthread.h>

int shared_resource;

void *thread_A(void *arg) {
    int i, data;
    for (i = 0; i < 1000000; i++) {
        data = shared_resource;
        data = data + 1;
        shared_resource = data;
    }
    pthread_exit(0);
}

void *thread_B(void *arg) {
    int i, data;
    for (i = 0; i < 1000000; i++) {
        data = shared_resource;
        data = data + 1;
        shared_resource = data;
    }
    pthread_exit(0);
}

int main() {
    pthread_t t1;
    pthread_t t2;
    shared_resource = 0;

    pthread_setconcurrency(2);
    pthread_create(&t1, NULL, (void *)thread_A, 0);
    pthread_create(&t2, NULL, (void *)thread_B, 0);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("main(): shared_resource == %d\n", shared_resource);
}
