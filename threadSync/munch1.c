/***
* A program to demonstrate thread synchronization
* Sushma K N <kudlurnirvan@wisc.edu>
* Srujana <srujana@wisc.edu>
*
* File to read data from reader buffer, convert whitespace to asterisk and write to Munch2 buffer
*
*/
#ifndef THREADDEMO_MUNCH1_c
#define THREADDEMO_MUNCH1_c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "munch1.h"
#include "Queue.h"
#include "utility.h"

void * convertSpaceToAsterisk(void *queue)
{
    readWriteQueue *newStruct = (readWriteQueue *) queue;
    Queue * readQueue = newStruct->readQueue;
    Queue * writeQueue = newStruct->writeQueue;

    while (1) {
        char * msg = DequeueString(readQueue);
        if (msg == NULL) {
            EnqueueString(writeQueue, msg);
            break;
        }
        char  *spaceIndexString = NULL;
        while( (spaceIndexString = index(msg, ' ')) != NULL) {
            long index  = spaceIndexString - msg;
            msg[index] = '*';
        }
        EnqueueString(writeQueue, msg);
    }
    pthread_exit(0);
}

#endif