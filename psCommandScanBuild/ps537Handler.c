/***
 * A simple program to generate ps command
 * Srujana <srujana@wisc.edu>
 * Sushma K N <kudlurnirvan@wisc.edu>
 * This file is used to handle errors in process status command input
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "ps537Handler.h"

#include "processUtility.h"
#include "dirRead.h"
#include "parseCommand.h"

typedef char * string;

void execute537PSCommand(int argsCount, char *args[]) {

    if (argsCount==1) {
        dirRead(argsCount, args);
    } else {
        int pid = -1;
        for(int i=1; i<argsCount; i++) {

            int temp = validateForPid(argsCount, args, i);
            if (temp!=-1 ) {
                pid = temp;
            }
            validateForRestCLI(argsCount, args, i, "-c");
            validateForRestCLI(argsCount, args, i, "-s");
            validateForRestCLI(argsCount, args, i, "-S");
            validateForRestCLI(argsCount, args, i, "-v");
            validateForRestCLI(argsCount, args, i, "-U");
        }

        if (pid == -1) {
            dirRead(argsCount, args);
        } else {
            int pids[1] = {pid};
            char* flag = accessValidatePid(pid);
            if (strcmp(flag,"true")==0) {
                parseCommand(argsCount, args, pids);
            } else {
                printf("\nSorry you do not have right permissions to check process info with pid: %d", pid);
            }
        }

    }
}

int validateForPid(int argCount, char *args[], int i) {
    if (args[i]!=NULL){
        if (strstr(args[i], "-p")!=NULL) {
            string pid =  getOtherPartOfSubstring(strstr(args[i], "-p"));
            if (pid==NULL && (i+1)<argCount) {
                string nextArgument = args[i+1];
                if (nextArgument!=NULL && (strcmp(&nextArgument[0],"-")!=0)) {
                    return atoi(nextArgument);
                } else {
                    printf("\nEnter a valid argument -p<pid> -s -U -S -v -c\n");
                    exit(1);
                }

            } else if (pid==NULL) {
                printf("\nEnter a valid argument -p<pid> -s -U -S -v -c\n");
                exit(1);
            } else {
                return atoi(pid);
            }
        }
    }
     return -1;

}

void validateForRestCLI(int argCount, char *args[], int i, char *subString) {

    if (args[i]!=NULL) {
        if (strstr(args[i], subString) != NULL) {
            string subPart = getOtherPartOfSubstring(strstr(args[i], subString));
            string nextArgument = args[i + 1];
            if (nextArgument!=NULL) {
                if (subPart == NULL && (i + 1) < argCount) {
                    if (strstr(nextArgument, "-")==NULL) {
                        printf("\nEnter a valid argument -p<pid> -s -U -S -v -c\n");
                        exit(1);
                    }
                } else if ((i + 1) < argCount && strstr(nextArgument, "-")==NULL) {
                    printf("\nEnter a valid argument -p<pid> -s -U -S -v -c\n");
                    exit(1);
                }
            }
        }
    }
}

string getOtherPartOfSubstring(string inputString) {

    if (inputString!=NULL) {

        string newSubstring=inputString;
        size_t length = strlen(inputString) - 2;
        puts(inputString+2);
        if(length > 0) {
            newSubstring = inputString+2;
           return newSubstring;
        }

    }
    return NULL;
}