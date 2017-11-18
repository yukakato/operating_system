#include <pthread.h>
#include <stdio.h>

void *thread1(void *arg) {
    for (;;) printf("Thread A\n");
}

void *thread2(void *arg) {
    for (;;) printf("Thread B\n");
}

void *thread3(void *arg) {
    for (;;) printf("Thread C\n");
}

int main() {
    pthread_t a, b, c;
    pthread_create(&a, NULL, thread1, NULL);
    pthread_create(&b, NULL, thread2, NULL);
    pthread_create(&c, NULL, thread3, NULL);

    pthread_join(a, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);
    return 0;
}
