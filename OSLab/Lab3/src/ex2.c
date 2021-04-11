#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) 
{
    pid_t pida, pidb, pidc, pidd, pidf, pidg, pidi;
    
    pida = fork();
    if (pida == 0) {
        pidb = fork();
        if (pidb == 0) {
            printf("In e: pid=%d\n", getpid());
        }
        else if (pidb > 0) {
            wait(NULL);
            pidf = fork();
            if (pidf == 0) {
                printf("In f: pid=%d\n", getpid());
            }
            else if (pidf > 0) {
                wait(NULL);
                printf("In b: pid=%d\n", getpid());
            }
        }
    }
    else if (pida > 0) {
        wait(NULL);
        pidc = fork();
        if (pidc == 0) {
            pidg = fork();
            if (pidg == 0) {
                pidi = fork();
                if (pidi == 0) {
                    printf("In i: pid=%d\n", getpid());
                }
                else if (pidi > 0) {
                    wait(NULL);
                    printf("In g: pid=%d\n", getpid());
                }
            }
            else if (pidg > 0) {
                wait(NULL);
                printf("In c: pid=%d\n", getpid());
            }
        }
        else if (pidc > 0) {
            wait(NULL);
            pidd = fork();
            if (pidd == 0) {
                printf("In d: pid=%d\n", getpid());
            }
            else if (pidd > 0) {
                wait(NULL);
                printf("In a: pid=%d\n", getpid());
            }
        }
    }
}
