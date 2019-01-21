/***
 * A simple program to generate ps command
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * This file is used to fetch process user time information based on processID
 *
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#ifndef OSPROJ_PUTIME_C
#define OSPROJ_PUTIME_C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include "processUtime.h"
#include "processUtility.h"
#endif

typedef char * string;

char * getProcessUtime(int pid)
{
    if(pid>0) {

        char *filePath = getProcUtimePathName(pid);
        char *line = readSpecificLineFromFile(filePath, 1);

        if (line!= NULL) {
            char str[1000];
            char *rest;
            strcpy(str, line);
            char *procUtime = strtok_r(str, " \t", &rest);
            for (int count=1; count<16; count++) {
                procUtime = strtok_r(NULL, " \t", &rest);
            }
            char *result = (char *) malloc(sizeof(char)*strlen(procUtime));
            memcpy(result, procUtime, strlen(procUtime));
            if (result!=NULL) {
                strcat(result,"\0");
            }
            return result;
        }
    }
    return NULL;
}

char * getProcUtimePathName(int pid) {

    char *filePath;
    asprintf(&filePath, "/proc/%d/stat", pid);
    return filePath;
}

