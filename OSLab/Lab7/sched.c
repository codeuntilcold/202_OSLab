// sched.c //
#include "queue.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define TIME_UNIT		100			// Microseconds

static struct pqueue_t in_queue;	// Queue for incoming processes
static struct pqueue_t ready_queue;	// Queue for ready processes

static int load_done = 0;

// Maximum amount of time a process is allowed to be run on CPU before being swapped out
static int timeslot;	

// Emulate the CPU
void* cpu(void* arg);

// Emulate the loader
void* loader(void* arg);

// Read the list of process to be executed from stdin
void load_task();

int main() {
	pthread_t cpu_id;
	pthread_t loader_id;
	
	initialize_queue(&in_queue);
	initialize_queue(&ready_queue);
	
	load_task();
	
	pthread_create(&cpu_id, NULL, cpu, NULL);
	pthread_create(&loader_id, NULL, loader, NULL);
	
	pthread_join(cpu_id, NULL);
	pthread_join(loader_id, NULL);
	
	pthread_exit(NULL);
}

void* cpu(void* arg) {

}

void* loader(void* arg) {

}

void load_task() {

}




	
	
	
