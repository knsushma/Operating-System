/***
* A program to demonstrate thread synchronization
* Sushma K N <kudlurnirvan@wisc.edu>
* Srujana <srujana@wisc.edu>
*
* Utility file to print error values and to set buffer and queue size
*
*/

#ifndef THREADDEMO_UTILITY_H
#define THREADDEMO_UTILITY_H

#include "Queue.h"

#define QUEUE_SIZE  1024
#define BUFFER_SIZE  1024

typedef struct readWriteQueue {
    Queue * readQueue;
    Queue * writeQueue;
}readWriteQueue;

readWriteQueue * getReadWriteQueue(Queue* q1, Queue* q2);
void pthreadPrintErrorCodeAndExit( char * pthreadFailed, int errCode);
void pthreadJoinPrintErrorCodeAndExit( char * pthreadFailed, int errCode);

#endif