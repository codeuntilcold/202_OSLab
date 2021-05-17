#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

static volatile int counter = 0;
// pthread_mutex_t lock;
// void* mythread(void* arg) {
//     printf("%s: begin\n", (char*)arg);
//     int i;
//     pthread_mutex_lock(&lock);
//     for (i = 0; i < 1e7; i++) {
//         counter = counter + i;
//     }
//     pthread_mutex_unlock(&lock);
//     return NULL;
// }

#define NUM_TICKETS 35
#define NUM_SELLERS 4
#define true 1
#define false 0
static int numTickets = NUM_TICKETS;
static sem_t ticketLock;
void* sellTicket(void* arg) {
    int done = false;
    int numSoldByThisThread = 0;
    int tid = (int) arg;
    while (!done) {
        sem_wait(&ticketLock);
        if (numTickets == 0)
            done = true;
        else {
            numTickets--;
            numSoldByThisThread++;
            printf("Thread %d sold one (%d left)\n", tid, numTickets);
        }
        sem_post(&ticketLock);
        sleep(1);
    }
    printf("Thread %d sold %d tickets\n", tid, numSoldByThisThread);
    pthread_exit(NULL);
}

#define MAX_ITEMS 3
#define THREADS 2
#define LOOPS 2*MAX_ITEMS

int buffer[MAX_ITEMS];
int fill = 0;
int use = 0;

sem_t empty;
sem_t full;
sem_t lock;

void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % MAX_ITEMS;
}
int get() {
    int tmp = buffer[use];
    use = (use + 1) % MAX_ITEMS;
    return tmp;
}
void* producer(void* arg) {
    int i;
    int tid = (int) arg;
    for(i = 0; i < LOOPS; i++) {
        sem_wait(&empty);
        sem_wait(&lock);
        put(i);
        sem_post(&lock);
        printf("Producer %d --> data %d\n", tid, i);
        sleep(1);
        sem_post(&full);
    }
    for(i = 0; i < LOOPS; i++) {
        sem_wait(&empty);
        put(-1);
        sem_post(&full);
    }
    pthread_exit(NULL);
}
void* consumer(void* arg) {
    int i, tmp = 0;
    int tid = (int) arg;
    while (tmp != -1) {
        sem_wait(&full);
        sem_wait(&lock);
        tmp = get();
        sem_post(&lock);
        printf("Consumer %d <-- data %d\n", tid, tmp);
        sleep(1);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}


int main(int argc, char** argv) {
    // pthread_t p1, p2;
    // printf("main: begin (counter = %d)\n", counter);
    // pthread_create(&p1, NULL, mythread, "A");
    // pthread_create(&p2, NULL, mythread, "B");
    // pthread_join(p1, NULL);
    // pthread_join(p2, NULL);
    // printf("main: done with both (counter = %d)\n", counter);
    // return 0;

    // int i;
    // int tid[NUM_SELLERS];
    // pthread_t sellers[NUM_SELLERS];
    // sem_init(&ticketLock, 0, 1);
    // for (i = 0; i < NUM_SELLERS; i++) {
    //     tid[i] = i;
    //     pthread_create(&sellers[i], NULL, sellTicket, (void*)tid);
    // }
    // for (i = 0; i < NUM_SELLERS; i++) {
    //     pthread_join(sellers[i], NULL);
    // }
    // sem_destroy(&ticketLock);
    // pthread_exit(NULL);
    // return 0;

    int i, j;
    int tid[THREADS];
    pthread_t producers[THREADS];
    pthread_t consumers[THREADS];

    sem_init(&empty, 0, MAX_ITEMS);
    sem_init(&full, 0, 0);
    sem_init(&lock, 0, 1);

    for (i = 0; i < THREADS; i++) {
        tid[i] = i;
        pthread_create(&producers[i], NULL, producer, (void*)tid[i]);
        pthread_create(&consumers[i], NULL, consumer, (void*)tid[i]);
    }
    for (i = 0; i < THREADS; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}

