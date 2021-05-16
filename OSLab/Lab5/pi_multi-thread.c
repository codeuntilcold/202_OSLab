#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 4

int pit;
int seed;
void* runner(void* param);

int main(int argc, char** argv) 
{
    if (argc != 2) {
        perror("Invalid, must provide number of points");
        exit(1);
    }

    clock_t s = clock();

    pthread_t tid[NUM_THREADS];
    int nPoints = atoi(argv[1]);
    int pic = 0;
    pit = nPoints / NUM_THREADS;
    
    for (int i = 0; i < NUM_THREADS; i++) {
        int rc = pthread_create(&tid[i], NULL, runner, argv[1]);
        // int rc = pthread_create(&tid[i], NULL, runner, (void*)(param / NUM_THREADS));
        if (rc) {
            perror("Threading error\n");
            exit(1);
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        int *result;
        pthread_join(tid[i], (void**)&result);
        // printf("result = %d\n", *result);
        pic += *result;
    }
    clock_t e = clock() - s;
    printf("pi = %f\n", (float) 4 * pic / nPoints);
    printf("runtime: %fs\n", (float) e / CLOCKS_PER_SEC / NUM_THREADS);
}

void* runner(void* param) {
    int* res = malloc(sizeof(int));
    *res = 0;
    float x, y;
    for (int i = 0; i < pit; i++) {
        x = (float) rand_r(&seed) / RAND_MAX;
        y = (float) rand_r(&seed) / RAND_MAX;
        if (x * x + y * y <= 1)
            (*res)++;
    }
    // printf("result = %d\n", *res);
    pthread_exit((void*)res);
}



