/***
 * A simple program to generate ps command
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * It is a Utility file which includes definitions of functions which are generic and used accross multiple files.
 *
 */
#ifndef OSPROJ_PUTILITY_C
#define OSPROJ_PUTILITY_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include "processUtility.h"
#endif

typedef char* string;

char * readSpecificLineFromFile(char *filePath, int readLine) {
    char *line = NULL;
    size_t len = 0;
    int count = 1;

    FILE *stream = fopen(filePath, "r");
    if (stream!=NULL) {
        while (getline(&line, &len, stream) != -1) {
            if (count == readLine) {
                char * data = line;
                return data;
            }
            count++;
        }
    }
    return NULL;
}

char * remove_spaces(const char *inputString)
{
    if (inputString!=NULL) {
        char output[255];
        char input[255];

        memset(output, '\0', sizeof(output));
        memset(input, '\0', sizeof(output));
        strcpy(input, inputString);
        int i, j = 0;
        for (i = 0; input[i] !='\0'; i++) {
            if (!isspace((unsigned char) input[i])) {
                output[j++] = input[i];
            }
        }
        char * result = (char *) malloc(sizeof(char)*strlen(output));
        memcpy(result, output, strlen(output));
        return result;
    }
    return NULL;
}

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}


int Opt_Arg_Check(char * optargs) {
    if(optargs!=NULL)
    {
        return 0;
    }
    return 1;
}

void printOutput(process proc) {
    if (proc.pid!=-1) {
        printf("PID: %d\t", proc.pid);
        if (proc.vMemory != NULL)
            printf("VirtualMemory: %s\t", proc.vMemory);
        if (proc.cLine != NULL)
            printf("CommandLine: %s\t", proc.cLine);
        if (proc.sTime != NULL)
            printf("System time: %s\t", proc.sTime);
        if (proc.uTime != NULL)
            printf("Utime: %s\t", proc.uTime);
        if (proc.pState != NULL)
            printf("State: %s\t", proc.pState);
        printf("\n");
    }
}
