/***
 * A simple program to generate ps command
 * Srujana <srujana@wisc.edu>
 * Sushma K N <kudlurnirvan@wisc.edu>
 * This file is used to fetch virtual memory consumed by a process based on processID
 *
 */
#ifndef OSPROJ_PVIRTUAL_C
#define OSPROJ_PVIRTUAL_C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "processVirtualMemory.h"
#include "processUtility.h"
#endif

char * getProcessVMUtilisation(int pid) {

    char *filePath;
    if(pid>0) {
        filePath = getProcVMPathName(pid);
        char *line = readSpecificLineFromFile(filePath, 1);

        if (line!=NULL) {
            char str[100];
            char *procVM;
            char *rest;

            strcpy(str, line);
            procVM = strtok_r(str, " :\t", &rest);
            char *result = (char *) malloc(sizeof(char)*strlen(procVM));
            memcpy(result,line, strlen(procVM));
            return result;
        }
    }
    return NULL;
}

char * getProcVMPathName(int pid) {

    char *filePath;
    asprintf(&filePath, "/proc/%d/statm", pid);
    return filePath;
}