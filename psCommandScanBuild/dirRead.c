/***
 * A simple program to generate ps command
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * This file will list all process ID's
 *
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#ifndef OSPROJ_DIRREAD_C
#define OSPROJ_DIRREAD_C

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "dirRead.h"
#include "processUtility.h"
#include "parseCommand.h"
#endif

typedef char * string;


int dirRead(int c, char *args[]) {
    DIR *myDirectory;
    struct dirent *myFile;
    int count =0;
    int p[100];


    if (c > 0) {
        myDirectory = opendir("/proc");
        if (myDirectory) {

            while ((myFile = readdir(myDirectory))) {
                char *filePath = getProcPathName(atoi(myFile->d_name));
                char *line = readSpecificLineFromFile(filePath, 9);
                if (line !=NULL && isUserIdMatching(line)==1){
                    p[count++] = atoi(myFile->d_name);
                }
            }
            for (int i =count; i < ((int)sizeof(p))/((int)sizeof(int)); i++) {
                p[count++] = -1;
            }
            qsort(p, (sizeof(p)/ sizeof(int)), sizeof(int), cmpfunc);

            parseCommand(c, args, p);
            closedir(myDirectory);
        } else if (errno == ENOENT)
            puts("This directory does not exist.");
        else if (errno == ENOTDIR)
            puts("This file is not a directory.");
        else if (errno == EACCES)
            puts("You do not have the right to open this folder.");
        else
            puts("That's a new error, check the manual.");
    } else
        puts("Sorry we need exactly 2 arguments.");
    return (0);
}

char* accessValidatePid (int pid) {
    DIR *myDirectory;
    struct dirent *myFile;
    int count =0;
    int pids[100];
    char *flag = "false";

    myDirectory = opendir("/proc");
    if (myDirectory) {

        flag = "false";
        while ((myFile = readdir(myDirectory))) {
            char *filePath = getProcPathName(atoi(myFile->d_name));
            char *line = readSpecificLineFromFile(filePath, 9);
            if (line != NULL && isUserIdMatching(line) == 1) {
                pids[count++] = atoi(myFile->d_name);
            }
        }
        for (int i = count; i < ((int)sizeof(pids))/((int)sizeof(int)); i++) {
            pids[count] = -1;
            count = count + 1;
        }
        qsort(pids, (sizeof(pids)/sizeof(int)), sizeof(int), cmpfunc);
        for (int i = 0; i<100; i++) {
            if (pids[i]==pid) {
                flag = "true";
            }
        }
        closedir(myDirectory);
    } else if (errno == ENOENT) {
        puts("This directory does not exist.");
    }
    else if (errno == ENOTDIR)
        puts("This file is not a directory.");
    else if (errno == EACCES)
        puts("You do not have the right to open this folder.");
    else
        puts("That's a new error, check the manual.");
    return flag;
}


char * getProcPathName(int pid) {

    char *filePath;
    asprintf(&filePath, "/proc/%d/status", pid);
    return filePath;
}

int isUserIdMatching(char *line) {
    if (line!=NULL) {
        char *procUid;
        char str[256];
        char *rest;
        strcpy(str, line);
        strtok_r(str, " \t", &rest);
        procUid = strtok_r(NULL, " \t", &rest);

        if (procUid != NULL) {
            if (atoi(procUid) == (int)getuid())  {
            //if (atoi(procUid) == 25456) {
                return 1;
            }
        }
    }
    return 0;
}

