/***
* A program to demonstrate thread synchronization
* Sushma K N <kudlurnirvan@wisc.edu>
* Srujana <srujana@wisc.edu>
*
* Utility file to print error values and to set buffer and queue size
*
*/
#ifndef THREADDEMO_UTILITY_C
#define THREADDEMO_UTILITY_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "utility.h"

readWriteQueue * getReadWriteQueue(Queue * q1, Queue * q2) {
    //readWriteQueue *newStruct = (readWriteQueue *) malloc(sizeof(readWriteQueue));
    readWriteQueue *newStruct = NULL;
    if ( ( newStruct = (readWriteQueue *) malloc(sizeof(readWriteQueue)) ) == NULL ) {
        fprintf(stderr, "Failed to allocate memory while creating structure of 2 queues.\n");
        exit(EXIT_FAILURE);
    }
    newStruct->readQueue = q1;
    newStruct->writeQueue = q2;
    return newStruct;
}

void pthreadPrintErrorCodeAndExit( char * pthreadFailed, int errCode) {
    fprintf(stderr,"Error - %s pthread_create() failed with return code: %d\n",pthreadFailed, errCode);
    exit(EXIT_FAILURE);
}

void pthreadJoinPrintErrorCodeAndExit( char * pthreadFailed, int errCode) {
    fprintf(stderr,"Error - %s pthread_join() failed with return code: %d\n",pthreadFailed, errCode);
    exit(EXIT_FAILURE);
}

#endif
