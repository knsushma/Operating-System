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

void execute537PSCommand(int argCount, char *args[]) {

    if (argCount==1) {
        dirRead(argCount, args);
    } else {
        char *pids[1] ={NULL};
        for(int i=1; i<argCount; i++) {

            char *temp = validateForPid(argCount, args, i, "-p");
            if (temp!=NULL) {
                pids[0] = temp;
            }
            validateForRestCLI(argCount, args, i, "-c");
            validateForRestCLI(argCount, args, i, "-s");
            validateForRestCLI(argCount, args, i, "-S");
            validateForRestCLI(argCount, args, i, "-v");
            validateForRestCLI(argCount, args, i, "-U");
        }

        if (pids[0]==NULL) {
            dirRead(argCount, args);
        } else {
            int pid = atoi(pids[0]);
            char* flag = accessValidatePid(pid);
            if (strcmp(flag,"true")==0) {
                parseCommand(argCount, args, pids);
            } else {
                printf("\nSorry you do not have right permissions to check process info with pid: %d", pid);
            }
        }

    }
}

char * validateForPid(int argCount, char *args[], int i, char *subString) {
    if (args[i]!=NULL){
        if (strstr(args[i], "-p")!=NULL) {
            string pid =  getOtherPartOfSubstring(strstr(args[i], "-p"));
            if (pid==NULL && (i+1)<argCount) {
                string nextArgument = args[i+1];
                if (nextArgument!=NULL && (strcmp(&nextArgument[0],"-")!=0)) {
                    return nextArgument;
                } else {
                    printf("\nfrom PID IF ");
                    printf("\nEnter a valid argument -p<pid> -s -U -S -v -c\n");
                    exit(1);
                }

            } else if ((i+2)<argCount) {
                printf("\nfrom PID ELSE");
                printf("\nEnter a valid argument -p<pid> -s -U -S -v -c\n");
                exit(1);
            }
            return pid;
        }
    }
     return NULL;

}

void validateForRestCLI(int argCount, char *args[], int i, char *subString) {

    if (args[i]!=NULL) {
        if (strstr(args[i], subString) != NULL) {
            string subPart = getOtherPartOfSubstring(strstr(args[i], subString));
            string nextArgument = args[i + 1];
            if (subPart == NULL && (i + 1) < argCount) {
                if (nextArgument != NULL && strstr(nextArgument, "-")==NULL) {
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