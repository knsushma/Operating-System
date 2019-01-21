/***
 * A program to demonstrate thread synchronization
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * Main thread which will create and initialize pthreads
 * Queue will be created and associated with respective threads.
 *
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
#include "reader.h"
#include "writer.h"
#include "munch1.h"
#include "munch2.h"
#include "utility.h"

int main() {

    pthread_t Reader, Munch1, Munch2, Writer;
    int pCreateRet1, pCreateRet2, pCreateRet3, pCreateRet4;
    int pJoinRet1, pJoinRet2, pJoinRet3, pJoinRet4;

    //Create String Queue
    Queue* readerBuffer = CreateStringQueue(QUEUE_SIZE);
    Queue* processBuffer = CreateStringQueue(QUEUE_SIZE);
    Queue* writerBuffer = CreateStringQueue(QUEUE_SIZE);

    //Pthread Create
    if  ( (pCreateRet1 = pthread_create(&Reader, NULL, streamReader, readerBuffer)) ) {
        pthreadPrintErrorCodeAndExit("Reader", pCreateRet1);
    }
    if ( (pCreateRet2 = pthread_create(&Munch1, NULL, convertSpaceToAsterisk,
                                       (void *) getReadWriteQueue(readerBuffer, processBuffer))) ) {
        pthreadPrintErrorCodeAndExit("Munch1", pCreateRet2);
    }
    if ( (pCreateRet3 = pthread_create(&Munch2, NULL, convertToUpper, (void *) getReadWriteQueue(processBuffer, writerBuffer))) ) {
        pthreadPrintErrorCodeAndExit("Munch2", pCreateRet3);
    }
    if ( (pCreateRet4 = pthread_create(&Writer, NULL, streamWriter, writerBuffer)) ) {
        pthreadPrintErrorCodeAndExit("Writer", pCreateRet4);
    }

    //Pthread Join
    if ( (pJoinRet1 = pthread_join(Reader, (void **) &pJoinRet1)) ) {
        pthreadJoinPrintErrorCodeAndExit("Reader", pJoinRet1);
    }
    if ( (pJoinRet2 = pthread_join(Munch1, (void **) &pJoinRet2)) ) {
        pthreadJoinPrintErrorCodeAndExit("Munch1", pJoinRet1);
    }
    if ( (pJoinRet3 = pthread_join(Munch2, (void **) &pJoinRet3)) ) {
        pthreadJoinPrintErrorCodeAndExit("Munch2", pJoinRet1);
    }
    if ( (pJoinRet4 = pthread_join(Writer, (void **) &pJoinRet4)) ) {
        pthreadJoinPrintErrorCodeAndExit("Writer", pJoinRet1);
    }

    //Print Queue Status
    fprintf(stderr,"Reader Queue status: \n");
    PrintQueueStats(readerBuffer);
    fprintf(stderr,"Munch1 Queue status: \n");
    PrintQueueStats(processBuffer);
    fprintf(stderr,"Munch2 Queue status: \n");
    PrintQueueStats(writerBuffer);

    return 0;
}