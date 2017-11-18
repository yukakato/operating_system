#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
    pid_t pid;
    int status;
    printf("P: parent\n");
    sleep(10);
    if ((pid = fork()) != 0) {
        printf("P: child created\n");
        wait(&status);
        printf("P: child exited\n");
        sleep(10);
    } else {
        printf("C: child\n");
        sleep(10);
        printf("C: exiting\n");
        exit(0);
    }
}
