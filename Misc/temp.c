#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int value = 5;

int main(int argc, char** argv)
{
    // printf("Process ID: %d\n", getpid());
    // printf("Parent process ID: %d\n", getppid());
    // printf("My group: %d\n", getpgrp());

    // switch (fork())
    // {
    // case 0:
    //     printf("I am the child: pid=%d\n", getpid());
    //     printf("My parent: pid=%d\n", getppid());
    //     break;
    // default:
    //     printf("I am the parent: pid=%d\n", getpid());
    //     break;
    // case -1:
    //     printf("Failed\n");
    //     break;
    // }

    // CREATE 4 HELLOS
    // printf("hi\n");
    // fork();
    // fork();
    // printf("hello\n");

    // pid_t child_pid;
    // child_pid = fork();
    // if (child_pid == -1) {
    //     perror("fork");
    //     exit(1);
    // }
    // if (child_pid == 0) {
    //     printf("Hello, ");
    //     fflush(stdout);
    // }
    // else {
    //     // wait();
    //     printf("World!\n");
    //     fflush(stdout);
    // }

    // int timestamp = 0;
    // printf("pid=%d\n", getpid());
    // while (1) {
    //     printf("Time: %5d\n", timestamp++);
    //     sleep(1);
    // }

    // pid_t pid;
    // pid = fork();
    // if (pid == 0) {
    //     value += 15;
    //     return 0;
    // }
    // else if (pid > 0) {
    //     wait(NULL);
    //     printf("Parent value: %d\n", value);
    //     return 0;
    // }

    // pid_t A = fork();
    // if(A==0){
    //     printf("pid=%d\n", getpid());
    // }
    // pid_t B = fork();
    // if(B==0){
    //     printf("pid=%d\n", getpid());
    // }
    // pid_t C = fork();
    // if(C==0){
    //     printf("pid=%d\n", getpid());
    // }

    pid_t child_pid;
    sigset_t mask, oldmask;

    child_pid = fork();

    if (child_pid == -1) { perror("fork"); exit(1); }
    if (child_pid == 0) {
        signal(SIGUSR1, );    // Set up signal
        sigemptyset(&mask);             // Set up mask to
        sigaddset(&mask, SIGUSR1);      // temporarily block

        sigprocmask(SIG_BLOCK, &mask, &oldmask);    // Wait
        while (!usr_interrupt)
            sigsuspend(&oldmask);
        sigprocmask(SIG_UNBLOCK, &mask, NULL);

        printf("World!\n");
        fflush(stdout);
    }
    else {
        printf("Hello, ");
        fflush(stdout);
        kill(child_pid, SIGUSR1);
        wait();
    }
 
    return 0;
}
