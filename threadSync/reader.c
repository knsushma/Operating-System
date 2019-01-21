/***
* A program to demonstrate thread synchronization
* Sushma K N <kudlurnirvan@wisc.edu>
* Srujana <srujana@wisc.edu>
*
* File to read data from stdin and write to Reader buffer.
*
*/
#ifndef THREADDEMO_READER_C
#define THREADDEMO_READER_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Queue.h"
#include "utility.h"

void * streamReader(void *queue) {

    int charCount = 0;
    char inputCharString[BUFFER_SIZE];
    int bufferExceeded = 0;

    while (1) {
        char inputCharacter = (char) getc(stdin);
        if ( inputCharacter == EOF) {
            if (charCount>0 && bufferExceeded == 0) {
                inputCharString[charCount] = '\0';
                char * inputString = NULL;
                if ( (inputString = (char *) malloc(charCount * sizeof(char) + 1)) == NULL ) {
                    fprintf(stderr, "Reader Failed to allocate memory(heap:Malloc).\n");
                    exit(1);
                }
                strncpy(inputString, inputCharString, charCount);
                EnqueueString(queue, inputString);
            }
            break;
        }
        if ( inputCharacter != '\n') {
            if (charCount < (BUFFER_SIZE-1)) {
                inputCharString[charCount] = inputCharacter;
                charCount = charCount + 1;
            } else {
                bufferExceeded = 1;
            }
        } else if ( bufferExceeded == 0) {
            inputCharString[charCount] = '\0';
            char * inputString = NULL;
            if ( (inputString = (char *) malloc(charCount * sizeof(char) + 1)) == NULL ) {
                fprintf(stderr, "Reader Failed to allocate memory(heap:Malloc).\n");
                exit(1);
            }
            strncpy(inputString, inputCharString, charCount);
            EnqueueString(queue, inputString);
            charCount = 0;
        } else {
            fprintf(stderr,"Line is too long, its discarded.\n");
            bufferExceeded = 0;
            charCount = 0;
        }
    }
    EnqueueString(queue, NULL);
    pthread_exit(0);
}

#endif
