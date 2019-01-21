/***
 * A simple program to generate ps command
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * This file is used to fetch process system time information based on processID
 *
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#ifndef OSPROJ_PSTIME_C
#define OSPROJ_PSTIME_C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include "processSystime.h"
#include "processUtility.h"
#endif

typedef char * string;

char * getProcessSystime(int pid)
{
    if(pid>0) {
        char *filePath = getProcSystimePathName(pid);
        char *line = readSpecificLineFromFile(filePath, 1);

        if (line!=NULL) {
            char str[1000];
            char *procSystime;
            char *rest;

            strcpy(str, line);
            procSystime = strtok_r(str, " \t", &rest);
            for (int count=1; count<15; count++) {
                procSystime = strtok_r(NULL, " \t", &rest);
            }
            char *data = (char *) malloc(sizeof(char)*strlen(procSystime));
            memcpy(data, procSystime, strlen(procSystime));
            if (data!=NULL) {
                strcat(data,"\0");
            }
            return data;
        }
    }
    return NULL;
}

char * getProcSystimePathName(int pid) {

    char *filePath;
    asprintf(&filePath, "/proc/%d/stat", pid);
    return filePath;
}

