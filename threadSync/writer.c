/***
* A program to demonstrate thread synchronization
* Sushma K N <kudlurnirvan@wisc.edu>
* Srujana <srujana@wisc.edu>
*
* File to read from Writer buffer and write data to stdout stream
*
*/
#ifndef THREADDEMO_WRITER_C
#define THREADDEMO_WRITER_C

#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define counter 0

void * streamWriter(void* queue) {
    int stringCount = counter;
    while(1) {
        char * outputString = DequeueString((Queue *)queue);
        if (outputString == NULL) {
           printf("Number of strings processed: %d\n", stringCount);
	   break;
        }
	stringCount += 1;
        printf("%s\n",outputString);
        //free(outputString);
	outputString = NULL;
    }
    pthread_exit(0);
}

#endif
