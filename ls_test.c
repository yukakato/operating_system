#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
    pid_t pid;
    int status;
    if ((pid = fork()) != 0) {
        wait(&status);
    } else {
        execlp("ls", "ls", NULL);
    }
}
