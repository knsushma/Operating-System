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
#include "processSystime.h"

typedef char * string;

int getProcessSystime(int pids[])
{
    printf("Inside function SysTime\n");
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
                    if (count == 16) {
                        break;
                    }
                }
            }
            printf("SysTime: %s\n", array[15]);
            fclose(stream);
            *filePath = NULL;
        }
    }
    return 1;
}

//int main() {
//    int pids[] = {1745};//{32490};
//    getProcessSystime(pids);
//    return 0;
//}

//#include <stdio.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <sys/types.h>
//#include <dirent.h>
//#include <errno.h>
//#include <string.h>
//int getProcessSystime(int c, char *v[], int pids[])
//{
//    struct stat *buf;
//
//    printf("Inside system time command");
//    if(sizeof(pids)>0) {
//        for (int i = 0; i < sizeof(pids) / sizeof(int); i++) {
//
//            printf("i value: %d",i);
//
//            char *filePath;
//            asprintf(&filePath, "/proc/%c/stat/stime", pids[i]);
//
//            printf("filePath to check \"%s\"\n",filePath);
//
//            int cLarg = open(filePath, O_RDONLY);
//            if (cLarg < 0) {
//                printf("error!!\n");
//                exit(1);
//            } else {
//                printf("systime=%d\n", cLarg);
//                char *c = (char *) calloc(100, sizeof(char));
//                int sz = read(cLarg, c, 10);
//                printf("called read(% d, c, 10). returned that" " %d bytes were read.\n", cLarg, sz);
//                c[sz] = '\0';
//                printf("Those bytes are as follows: % s\n", c);
//            }
//            *filePath = NULL;
//            free(*filePath);
//        }
//    }
//
//       return 1;
//}
