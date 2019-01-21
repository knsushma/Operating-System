/***
* A program to demonstrate thread synchronization
* Sushma K N <kudlurnirvan@wisc.edu>
* Srujana <srujana@wisc.edu>
*
* File to demonstrate Queue functionality with synchronization between threads
*
*/

#ifndef THREADDEMO_QUEUE_H
#define THREADDEMO_QUEUE_H

#include <stdio.h>
#include <pthread.h>

typedef struct Queue
{
    int front, rear, size;
    int capacity;
    char** data;
    int enqueueCount;
    int dequeueCount;
    int enqueueBlockCount;
    int dequeueBlockCount;
    pthread_cond_t empty, full;
    pthread_mutex_t  mutex;
}Queue;

Queue * CreateStringQueue(int capacity);
void EnqueueString(Queue *queue, char *string);
char * DequeueString(Queue *queue);
void PrintQueueStats(Queue *queue);

int isFull(Queue* queue);
int isEmpty(Queue* queue);

#endif
