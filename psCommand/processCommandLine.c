/***
 * A simple program to generate ps command
 * Srujana <srujana@wisc.edu>
 * Sushma K N <kudlurnirvan@wisc.edu>
 *
 * This file is used to fetch command line details which triggered the respective process based on processID
 *
 */
#ifndef OSPROJ_COMMANDLINE_C
#define OSPROJ_COMMANDLINE_C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "processCommandLine.h"
#include "processUtility.h"
#endif
char * getCommandLineOfProcess(int pid) {

    char *filePath;
    if(pid>0) {
        filePath = getProcCmdLinePathName(pid);
        char *line = readSpecificLineFromFile(filePath, 1);

        if (line!=NULL) {
            line = remove_spaces(line);
            char *result = (char *) malloc(sizeof(char)*strlen(line));
            memcpy(result,line, strlen(line));
            return result;
        }
    }
    return NULL;
}

char * getProcCmdLinePathName(int pid) {
    char *filePath;
    asprintf(&filePath, "/proc/%d/cmdline", pid);
    return filePath;
}
