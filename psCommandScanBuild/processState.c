/***
 * A simple program to generate ps command
 * Srujana <srujana@wisc.edu>
 * Sushma K N <kudlurnirvan@wisc.edu>
 *
 * This file is used to fetch process state information based on processID
 *
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#ifndef OSPROJ_PSTATE_C
#define OSPROJ_PSTATE_C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include "processState.h"
#include "processUtility.h"
#endif

typedef char * string;

char * getProcessState(int pid) {

    if(pid>0) {
        char *filePath = getProcStatPathName(pid);
        char *line = readSpecificLineFromFile(filePath, 3);

        if (line!=NULL) {
            char str[255];
            char *procStatus;
            char *rest;
            strcpy(str, line);
            strtok_r(str, " \t", &rest);
            procStatus = strtok_r(NULL, " \t", &rest);

            char *result = (char *) malloc(sizeof(char)*strlen(procStatus));
            memcpy(result,procStatus, strlen(procStatus));
            if (result!=NULL) {
                strcat(result,"\0");
            }
            return result;
        }
    }
    return NULL;
}

char * getProcStatPathName(int pid) {
    char *filePath;
    asprintf(&filePath, "/proc/%d/status", pid);
    return filePath;
}



