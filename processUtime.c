//
// Created by Sushma K N on 26/09/18.
//
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include "processUtime.h"

typedef char * string;

int getProcessUtime(int pids[])
{
    printf("Inside UTime function\n");
    if(sizeof(pids)>0) {

        for (int i = 0; i < (sizeof(pids) / sizeof(int)) -1 ; i++) {
            FILE *stream;
            char line[256];
            int count = 1;
            char *data = NULL;

            char *filePath;
            asprintf(&filePath, "/proc/%d/stat", pids[i]);
            stream = fopen(filePath, "r");

            while (fgets(line, sizeof(line), stream)) {
                    data = line;
                    break;
            }

            char * stringSplit;
            string array[15];
            //printf("\nreading from function: %s",readSpecificLineFromFile(filePath, 5));
            if (data!=NULL) {
                stringSplit = strtok (data," ,.-");
                while (stringSplit != NULL)
                {
                    char *filePath;
                    asprintf(&filePath, "%s", stringSplit);
                    array[count] = filePath;
                    count++;
                    stringSplit = strtok (NULL, " ,.-");
                    if (count == 15) {
                        break;
                    }
                }
            }
            printf("UTime: %s\n", array[14]);
            fclose(stream);
            *filePath = NULL;
        }
    }
    return 1;
}

//int main() {
//    int pids[] = {1745};//{32490};
//    getProcessUtime(pids);
//    return 0;
//}






