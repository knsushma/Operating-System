/***
 * A simple program to generate ps command
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * This file will list all process ID's
 *
 */
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
    string procs;
    int count =0;
    int p[10];

    printf("c  = %d, v vector = %s\n", c, args[1]);
    if (c > 0) {
        myDirectory = opendir("/proc");
        if (myDirectory) {
            puts("OK the directory is opened, let's see its files:");

            while ((myFile = readdir(myDirectory))) {
                char *filePath = getProcPathName(atoi(myFile->d_name));
                char *line = readSpecificLineFromFile(filePath, 9);
                if (line !=NULL && isUserIdMatching(line)==1){
                    p[count++] = atoi(myFile->d_name);
                }
            }
            for (int i =count; i< sizeof(p)/sizeof(int); i++) {
                p[count++] = -1;
            }
            qsort(p, (sizeof(p)/ sizeof(int)), sizeof(int), cmpfunc);
            parseCommand(c, args, p);
            printf("\n\n\n");
            if (closedir(myDirectory) == 0)
                puts("The directory is now closed.");
            else
                puts("The directory can not be closed.");
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
    string procs;
    int count =0;
    int pids[1000];
    char *flag = "false";

    myDirectory = opendir("/proc");
    if (myDirectory) {
        puts("OK the directory is opened, let's see its files:");

        flag = "false";
        while ((myFile = readdir(myDirectory))) {
            char *filePath = getProcPathName(atoi(myFile->d_name));
            char *line = readSpecificLineFromFile(filePath, 9);
            if (line != NULL && isUserIdMatching(line) == 1) {
                pids[count++] = atoi(myFile->d_name);
            }
        }
        for (int i = count; i < sizeof(pids)/sizeof(int); i++) {
            pids[count] = 0;
            count = count +1;
        }
        qsort(pids, (sizeof(pids)/sizeof(int)), sizeof(int), cmpfunc);
        for (int i = 0; i<1000 ; i++) {
            if (pids[i]==pid) {
                flag = "true";
            }
        }
        if (closedir(myDirectory) == 0)
            puts("The directory is now closed.");
        else
            puts("The directory can not be closed.");
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


void getAllPidsFromProcDir(int c, char *args[]) {
    DIR *myDirectory;
    struct dirent *myFile;
    string procs;
    int count =0;
    int pids[10];

    myDirectory = opendir("/proc");
    if (myDirectory) {
        puts("OK the directory is opened, let's see its files:");

        while ((myFile = readdir(myDirectory))) {
            char *filePath = getProcPathName(atoi(myFile->d_name));
            char *line = readSpecificLineFromFile(filePath, 9);
            if (line != NULL && isUserIdMatching(line) == 1) {
                pids[count++] = atoi(myFile->d_name);
            }
        }
        for (int i = count; i < sizeof(pids)/sizeof(int); i++) {
            pids[count++] = -1;
        }
        qsort(pids, (sizeof(pids) / sizeof(int)), sizeof(int), cmpfunc);
        parseCommand(c, args, pids);
        if (closedir(myDirectory) == 0)
            puts("The directory is now closed.");
        else
            puts("The directory can not be closed.");
    } else if (errno == ENOENT) {
        puts("This directory does not exist.");
    }
    else if (errno == ENOTDIR)
        puts("This file is not a directory.");
    else if (errno == EACCES)
        puts("You do not have the right to open this folder.");
    else
        puts("That's a new error, check the manual.");
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
        procUid = strtok_r(str, " \t", &rest);
        procUid = strtok_r(NULL, " \t", &rest);

        if (procUid != NULL) {
            if (atoi(procUid) == getuid())  {
                return 1;
            }
        }
    }
    return 0;
}

long getSizeOfDirectoryNames(char *dirPath) {
    long length = 0;
    DIR *directory = opendir(dirPath);
    struct dirent *file;
    if (directory) {
        while ((file = readdir(directory))) {
            length = length + strlen(file->d_name);
        }
    }
    return length;
}



