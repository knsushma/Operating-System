/***
* A program to demonstrate thread synchronization
* Sushma K N <kudlurnirvan@wisc.edu>
* Srujana <srujana@wisc.edu>
*
* File to demonstrate Queue functionality with synchronization between threads
*
*/

#ifndef THREADDEMO_QUEUE_C
#define THREADDEMO_QUEUE_C

#include "Queue.h"
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>


Queue* CreateStringQueue(int capacity)
{
    Queue* queue = NULL;
    if ( (queue = (Queue*) malloc(sizeof(Queue))) == NULL ) {
        fprintf(stderr, "Failed to create string Queue.\n");
        exit(EXIT_FAILURE);
    }
    queue->capacity = capacity;
    queue->data = NULL;
    if ( (queue->data = (char **) malloc(queue->capacity * sizeof(char *))) == NULL ) {
        fprintf(stderr, "Failed to allocate Queue item.\n");
        exit(EXIT_FAILURE);
    }
    queue->front = 0;
    queue->size = 0;
    queue->rear = -1;
    queue->enqueueCount = 0;
    queue->dequeueCount = 0;
    queue->enqueueBlockCount = 0;
    queue->dequeueBlockCount = 0;
    pthread_cond_init(&queue->full, NULL);
    pthread_cond_init(&queue->empty, NULL);
    pthread_mutex_init(&queue->mutex, NULL);
    return queue;
}

int isFull(Queue* queue) {
    if (queue->size == queue->capacity) {
        return 1;
    }
    return 0;
}

int isEmpty(Queue* queue) {
    if  (queue->size == 0) {
        return 1;
    }
    return 0;
}


void EnqueueString(Queue *queue, char * qElement)
{
    int lockError;
    if ( (lockError = pthread_mutex_lock(&queue->mutex)) ){
        fprintf(stderr, "Pthread mutex lock in EnQueue failed with error code: %d .\n", lockError);
        exit(EXIT_FAILURE);
    }
    if (isFull(queue))
    {
        queue->enqueueBlockCount++;
        int waitErrorCode;
        if ( (waitErrorCode = pthread_cond_wait(&queue->full, &queue->mutex)) ) {
            fprintf(stderr, "Pthread condition wait on Queue Full failed with error code: %d .\n", waitErrorCode);
            exit(EXIT_FAILURE);
        }
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = qElement;
    queue->size = queue->size + 1;
    if ( qElement != NULL ) {
        queue->enqueueCount++;
    }
    int signalError;
    if ( (signalError = pthread_cond_signal(&queue->empty)) != 0){
        fprintf(stderr, "Pthread cond signal failed in EnQueue with error code: %d .\n", signalError);
        exit(EXIT_FAILURE);
    }
    int unlockError;
    if ( (unlockError = pthread_mutex_unlock(&queue->mutex)) ){
        fprintf(stderr, "Pthread mutex unlock failed in EnQueue with error code: %d .\n", unlockError);
        exit(EXIT_FAILURE);
    }
}


char * DequeueString(Queue *queue)
{
    int lockError;
    if ( (lockError = pthread_mutex_lock(&queue->mutex)) ){
        fprintf(stderr, "Pthread mutex lock in DeQueue failed with error code: %d .\n", lockError);
        exit(EXIT_FAILURE);
    }
    if (isEmpty(queue))
    {
        queue->dequeueBlockCount++;
        int waitErrorCode;
        if ( (waitErrorCode = pthread_cond_wait(&queue->empty, &queue->mutex)) ) {
            fprintf(stderr, "Pthread condition wait on Queue Full failed with error code: %d .\n", waitErrorCode);
            exit(EXIT_FAILURE);
        }
    }
    char* item = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    if ( item != NULL ) {
        queue->dequeueCount++;
    }
    int signalError;
    if ( (signalError = pthread_cond_signal(&queue->full)) ){
        fprintf(stderr, "Pthread cond signal failed in DeQueue with error code: %d .\n", signalError);
        exit(EXIT_FAILURE);
    }
    int unlockError;
    if ( (unlockError = pthread_mutex_unlock(&queue->mutex)) ){
        fprintf(stderr, "Pthread mutex unlock failed in DeQueue with error code: %d .\n", unlockError);
        exit(EXIT_FAILURE);
    }
    return item;

}


void PrintQueueStats(Queue *queue)
{
    fprintf(stderr,"enqueueCount: %d\n", queue->enqueueCount);
    fprintf(stderr,"dequeueCount: %d\n", queue->dequeueCount);
    fprintf(stderr,"enqueueBlockCount: %d\n", queue->enqueueBlockCount);
    fprintf(stderr,"dequeueBlockCount: %d\n", queue->dequeueBlockCount);
    fprintf(stderr,"\n");
}

#endif