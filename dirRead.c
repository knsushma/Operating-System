#include <stdio.h>
#include "stdlib.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "parseCommand.h"

typedef char * string;
extern string getUidByPid(int pid);

int dirRead(int c, char *v[]) {
    DIR *myDirectory;
    struct dirent *myFile;
    string procs;
    int count =0;
    int p[10];
    printf("user Id for process 1745: %s ", getUidByPid(1745));

    printf("c  = %d, v vector = %s\n", c, v[1]);
     if (c ==1 || c == 2) {
        myDirectory = opendir("/proc");
        if (myDirectory) {
            puts("OK the directory is opened, let's see its files:");
            while ((myFile = readdir(myDirectory))) {
                printf("%s\n", myFile->d_name);
                string uid = getUidByPid(atoi(myFile->d_name));
                if (uid == getuid()) {
                    p[count++] = atoi(myFile->d_name);
                }
            }
            if (closedir(myDirectory) == 0)
                puts("The directory is now closed.");
            else
                puts("The directory can not be closed.");
            parseCommand(c, v, p);
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


string getUidByPid(int pid) {
    FILE *stream;
    char line[256];
    int count = 0;
    char *data = NULL;
    string userId=NULL;

    char *filePath;

    asprintf(&filePath, "/proc/%c/status", pid);
    stream = fopen(filePath, "r");

    while (fgets(line, sizeof(line), stream)) {
        count++;
        if (count == 9) {
            data = line;
            break;
        }
    }
    //printf("\nreading from function: %s",readSpecificLineFromFile(filePath, 5));
    if (data!=NULL) {
        //printf("dkvnksd: %c\n", data[7]);
        char * stringSplit;
        string array[3];
        int step = 1;
        //printf("\nreading from function: %s",readSpecificLineFromFile(filePath, 5));
        if (data!=NULL) {
            stringSplit = strtok (data," :");
            while (stringSplit != NULL)
            {
                char *str;
                asprintf(&str, "%s", stringSplit);
                array[step] = str;
                step++;
                stringSplit = strtok (NULL, " ,.-");
                if (step == 4) {
                    break;
                }
            }
        }
        printf("State: %s\n", array[2]);
        userId = array[2];
    }
    fclose(stream);
    *filePath = NULL;
    return userId;
}
