#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include "processVirMemory.h"

int getProcessVirtualMemory(int pids[])
{
    printf("Inside VM function");
    if(sizeof(pids)>0) {
        for (int i = 0; i < (sizeof(pids) / sizeof(int)) -1 ; i++) {

            printf("i value: %d",i);

            char *filePath;
            asprintf(&filePath, "/proc/%d/statm", pids[i]);
            printf("buffer one trying \"%s\"\n",filePath);

            int cLarg = open(filePath, O_RDONLY);
            if (cLarg < 0) {
                printf("error!!\n");
                exit(1);
            } else {
                char *c = (char *) calloc(100, sizeof(char));
                int sz = read(cLarg, c, 50);
                c[sz] = '\0';
                printf("Virtual Memory: % s\n", c);
            }

            *filePath = NULL;
        }
    }
    return 1;
}

//int main() {
//    int pids[] = {1745};//{32490};
//    getProcessVirtualMemory(pids);
//}


