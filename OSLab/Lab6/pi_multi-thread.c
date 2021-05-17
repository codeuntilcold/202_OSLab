#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4

int hit = 0;
int loops;
int seed;
void* runner(void* param);


pthread_mutex_t lock;


int main(int argc, char** argv) 
{
    if (argc != 2) {
        perror("Invalid, must provide number of points");
        exit(1);
    }
    clock_t s = clock();

    int total = atoi(argv[1]);
    loops = total / NUM_THREADS;
    
    pthread_t tid[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        int rc = pthread_create(&tid[i], NULL, runner, NULL);
        // int rc = pthread_create(&tid[i], NULL, runner, (void*)(param / NUM_THREADS));
        if (rc) {
            perror("Threading error\n");
            exit(1);
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }
    
    clock_t e = clock() - s;
    printf("pi = %f\n", (float) 4 * hit / total);
    printf("runtime: %fs\n", (float) e / CLOCKS_PER_SEC / NUM_THREADS);
}

void* runner(void* param) {
    float x, y;
    for (int i = 0; i < loops; i++) {
        x = (float) rand_r(&seed) / RAND_MAX;
        y = (float) rand_r(&seed) / RAND_MAX;
        if (x * x + y * y <= 1) {
            pthread_mutex_lock(&lock);
            hit++;
            pthread_mutex_unlock(&lock);        
        }
    }
    pthread_exit(NULL);
}



