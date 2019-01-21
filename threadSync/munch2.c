/***
* A program to demonstrate thread synchronization
* Sushma K N <kudlurnirvan@wisc.edu>
* Srujana <srujana@wisc.edu>
*
* File to read data from Munch2 buffer, convert lowercase letters to uppercase and write to writer buffer
*
*/
#ifndef THREADDEMO_MUNCH2_C
#define THREADDEMO_MUNCH2_C

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <pthread.h>
#include "munch2.h"
#include "Queue.h"
#include "utility.h"

void * convertToUpper(void * queue)
{
    readWriteQueue *newStruct = (readWriteQueue *) queue;
    Queue * readQueue = newStruct->readQueue;
    Queue * writeQueue = newStruct->writeQueue;

    while(1) {
        char *msg = DequeueString(readQueue);
        if (msg == NULL) {
            EnqueueString(writeQueue, msg);
            break;
        }
        long len = strlen(msg);
        for (int i=0; i<len; i++) {
            msg[i] = (char) toupper(msg[i]);
        }
        EnqueueString(writeQueue, msg);
    }
    pthread_exit(0);
}

#endif