//
// Created by Sushma K N on 23/09/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int getProcessStateByPid(int pids[]) {
    if(sizeof(pids)>0) {
        for (int i = 0; i < sizeof(pids)/sizeof(int); i++) {
            //printf("PIDS: %d", pids[i]);
            char state=open("cat /proc/[pid]/stat", O_RDONLY);
            printf("State of process with PID : %d is: %c", pids[i], state);

            char *c = (char *) calloc(100, sizeof(char));
            int sz = read(state, c, 10);

        }
    } else {
        printf("Empty process ID list found. Please provide PID to get process info.");
        return 0;
    }
   return 1;
}

int main(int c, char *args[]) {
    int pids[] = {13260};
    getProcessStateByPid(pids);
    return 0;
}


