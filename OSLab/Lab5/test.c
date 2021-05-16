#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// -- FIRST EG --
// void func(unsigned long number) {
//     unsigned long local_f = number;
//     printf("%2lu -> %p\n", local_f, &local_f);
//     local_f--;
//     if (local_f > 0) {
//         func(local_f);
//     }
// }
// int main() {
//     func(10);
// }

// -- SECOND EG --
#define NUM_THREADS 5
void* PrintHello(void* threadid) {
    long tid;
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    pthread_exit(NULL);
}
int main(int argc, char** argv) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for (t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void*)t);
        if (rc) {
            printf("ERROR; return from pthread_create() is %d", rc);
            exit(-1);
        }
        /* Sooo much synchronization */
    }
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }
    pthread_exit(NULL);
} 

// -- THIRD EG --
// unsigned long sum = 0;        // this data is shared by the threads
// void* runner(void* param);
// int main(int argc, char** argv) {
//     pthread_t tid;
//     pthread_attr_t attr;
//     if (argc < 2) {
//         fprintf(stderr, "usage: a.out <integer value>\n" );
//         return -1;
//     }
//     pthread_attr_init(&attr);
//     // clock_t s = time(0);
//     pthread_create(&tid, &attr, runner, argv[1]);
//     // while (1) {
//     //     printf("1 second has passed\n");
//     //     sleep(1);
//     // }
//     pthread_join(tid, NULL);
//     // clock_t e = time(0) - s;
//     printf("sum = %lu\n", sum);

//     // clock_t s = time(0);
//     // sum = 0;
//     // runner(argv[1]);
//     // clock_t e = time(0) - s;
//     // printf("sum = %lu \t\t\t in %f \n", sum, (float)e / CLOCKS_PER_SEC);
// }
// void* runner(void* param) {
//     int i, upper = atoi(param);
//     // sum = 0;
//     for(i = 1; i <= upper; i++)
//         sum += i;
//     // pthread_exit(NULL);
// }


