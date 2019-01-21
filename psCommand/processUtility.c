/***
 * A simple program to generate ps command
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * It is a Utility file which includes definitions of functions which are generic and used accross multiple files.
 *
 */
#ifndef OSPROJ_PUTILITY_C
#define OSPROJ_PUTILITY_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include "processUtility.h"
#endif

typedef char* string;

char * readSpecificLineFromFile(char *filePath, int readLine) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int count = 1;

    FILE *stream = fopen(filePath, "r");
    if (stream!=NULL) {
        while ((read = getline(&line, &len, stream)) != -1) {
            if (count == readLine) {
                char * data = line;
                return data;
            }
            count++;
        }
    }
    return NULL;
}

char * remove_spaces(const char *inputString)
{
    if (inputString!=NULL) {
        char output[255];
        char input[255];

        memset(output, '\0', sizeof(output));
        memset(input, '\0', sizeof(output));
        strcpy(input, inputString);
        int i, j = 0;
        for (i = 0; input[i] !='\0'; i++) {
            if (!isspace((unsigned char) input[i])) {
                output[j++] = input[i];
            }
        }
        char * result = (char *) malloc(sizeof(char)*strlen(output));
        memcpy(result, output, strlen(output));
        return result;
    }
    return NULL;
}

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}


int Opt_Arg_Check(char * optargs) {
    if(optargs!=NULL)
    {
        return 0;
    }
    return 1;
}

void printOutput(process proc) {
    if (proc.pid!=0) {
	    printf("PID: %d\t",proc.pid);
    if (proc.vMemory!=NULL)
        printf("VirtualMemory: %s\t",proc.vMemory);
    if (proc.cLine!=NULL)
        printf("CommandLine: %s\t",proc.cLine);
    if (proc.sTime!=NULL)
        printf("System time: %s\t",proc.sTime);
    if (proc.uTime!=NULL)
        printf("Utime: %s\t",proc.uTime);
    if (proc.pState!=NULL)
        printf("State: %s\t",proc.pState);
    printf("\n");
    }
}

int isPidMentioned(int n, char *args[]) {
    char arguments[256];
    int count =0;
    for(int i=1; i<n; i++) {
        if (strstr(args[i], "-p")!=NULL) {
            return 1;
        }
    }
    return 0;
}

char* read_file(char directory_name[], char file_name[255]) {
    FILE* file_pointer;
    char full_path[255]  =  "/proc/";
    char *line = NULL;
    size_t len = 0;
    strcat(full_path, directory_name);
    strcat(full_path , "/");
    strcat(full_path,file_name);
    file_pointer = fopen(full_path, "r");
    char *readLine;
    int count = 1;

    ssize_t read;
    char *token;
    while ((read = getline(&line, &len, file_pointer)) != -1) {
        if (count == 9) {
            token = strtok(line, " ");
            while (token != NULL) {
                printf("\n%s",token);
                token = strtok(NULL, " ");
            }
            return line;
        }
        count++;
    }
    fclose(file_pointer);
    return line;
}

char * getFilePath(char directory_name[],int pid, char file_name[255], char *filePath) {

    char full_path[255] = "/";
    char pidStr[255];
    sprintf( pidStr, "%d", pid );
    strcat(full_path, directory_name);
    strcat(full_path, "/");
    strcat(full_path, pidStr);
    strcat(full_path, "/");
    strcat(full_path, file_name);
    printf("filename: %s", full_path);

    char * result = (char *) malloc(sizeof(char)*255);
    memcpy(result, full_path, strlen(full_path));

    return result;

}

char * getSpecificTokenInString(char *inputString, char * delimiters, int tokenNumber) {

    char str[256];
    char *token=NULL;

    strcpy(str,inputString);
    token = strtok (str, delimiters);
    token = strtok (NULL, delimiters);
    printf("token: %s\n", token);
    char *line = token;

    return token;
}


char * tokenizeString(char *inputString, char *delimiter) {

    if (inputString!=NULL) {
        char str[256];
        char *rest = NULL;
        char *token;
        int count = 0;

        strcpy(str,inputString);
        for (token = strtok_r(str, " ", &rest); token != NULL; token = strtok_r(NULL, " ", &rest)) {
            if (count == 2) {
                return token;
            }
            count++;
        }
    }
    return NULL;
}
