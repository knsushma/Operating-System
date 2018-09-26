//
// Created by Sushma K N on 23/09/18.
//
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include "processInfoByPid.h"
//#include <opencl-c.h>

int getProcessInfoByPid(int pids[]) {
    if(sizeof(pids)>0) {
        for (int i = 0; i < (sizeof(pids)/sizeof(int))-1; i++) {
            //printf("PIDS: %d", pids[i]);
            struct stat sts;
            if (stat("/proc/<pid>", &sts) == -1 && errno == ENOENT) {
                printf("Process with PID: %d does not exist", pids[i]);
            } else {
                printf("process info will be displayed");
            }
        }
    }
    else {
        printf("Empty process ID list found. Please provide PID to get process info.");
        return 0;
    }
    return 1;
}

//int main() {
//    int pids[] = {13260};
//    getProcessInfoByPid(pids);
//}

