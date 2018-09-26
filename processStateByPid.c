//
// Created by Sushma K N on 23/09/18.
//
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include "processStateByPid.h"


typedef char * string;

//char* readSpecificLineFromFile(char *filePath, int readline) {
//    FILE *stream;
//    char line[256];
//    int count = 1;
//    char *data = NULL;
//
//    stream = fopen(filePath, "r");
//    if (stream!=NULL) {
//        while (fgets(line, sizeof(line), stream)) {
//            if (count == readline) {
//                data = line;
//                break;
//            }
//            count++;
//        }
//        fclose(stream);
//    }
//    return data;
//
//}
//
//int getProcessStateByPid(int pids[]) {
//
//
//    printf("Inside command line function");
//    if(sizeof(pids)>0) {
//
//        for (int i = 0; i < (sizeof(pids) / sizeof(int)) -1 ; i++) {
//            printf("i value: %d",i);
//
//            char *filePath;
//            asprintf(&filePath, "/proc/%d/status", pids[i]);
//            printf("buffer one trying \"%s\"\n",filePath);
//
//            printf("reading from function: %s\n",readSpecificLineFromFile(filePath, 3));
//            char *state = readSpecificLineFromFile(filePath, 3);
//            printf("jdsfbhjksdjb: %s\n", state);
//            if (state!=NULL) {
//                printf("jdsfbhjksdjb: %s\n", state);
//            }
//
//            *filePath = NULL;
//            free(*filePath);
//        }
//    }
//    return 1;
//}

int getProcessStateByPid(int pids[]) {

    printf("Inside State function\n");
    if(sizeof(pids)>0) {

        for (int i = 0; i < (sizeof(pids) / sizeof(int)) -1 ; i++) {
            FILE *stream;
            char line[256];
            int count = 0;
            char *data = NULL;

            char *filePath;
            asprintf(&filePath, "/proc/%d/status", pids[i]);
            stream = fopen(filePath, "r");

            while (fgets(line, sizeof(line), stream)) {
                count++;
                if (count == 3) {
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
            }
            fclose(stream);
            *filePath = NULL;

        }
    }
    return 1;
}


//int main() {
//    int pids[] = {1745};
//    getProcessStateByPid(pids);
//    return 0;
//}



