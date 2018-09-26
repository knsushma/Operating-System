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
int processUtime(int c, char *v[], int pids[])
{
    printf("Inside system time command");
    if(sizeof(pids)>0) {
        for (int i = 0; i < sizeof(pids) / sizeof(int); i++) {
            char *processPath = printf("/proc/%d/stat/utime", pids[i]);
            int cLarg = open(*processPath, O_RDONLY);
            if (cLarg < 0) {
                printf("error!!\n");
                return 0;
            } else {
                printf("systime=%d\n", cLarg);
            }
            char *c = (char *) calloc(100, sizeof(char));
            if (cLarg < 0) {
                perror("r1");
                exit(1);
            }
            int sz = read(cLarg, c, 10);
            printf("called read(% d, c, 10). returned that" " %d bytes were read.\n", cLarg, sz);
            c[sz] = '\0';
            printf("Those bytes are as follows: % s\n", c);

            *processPath = NULL;
            free(*processPath);
        }
    }

    return 1;
}


