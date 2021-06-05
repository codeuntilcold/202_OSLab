#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t *q)
{
	return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc)
{
	/* TODO: put a new process to queue [q] */
	if (q->size < MAX_QUEUE_SIZE)
	{
		q->proc[q->size] = proc;
		q->size += 1;
	}
}

struct pcb_t *dequeue(struct queue_t *q)
{
	/* TODO: return a pcb whose prioprity is the highest
	 * in the queue [q] and remember to remove it from q
	 * */
	if (q->size > 0)
	{
		int i = 0;
		struct pcb_t * temp = q->proc[0];
		int idx = 0;
		for (; i < q->size; i++)
		{
			if (q->proc[i]->priority > temp->priority){
				temp = q->proc[i];
				idx = i;
			}
		}
		for(int j = idx; j < q->size - 1; j++){
			q->proc[j] = q->proc[j+1];
		}
		q->proc[q->size - 1] = NULL;
		q->size -= 1;
		return temp;
	}
	return NULL;
}
