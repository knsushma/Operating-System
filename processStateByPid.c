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
            char *processPath = printf("cat /proc/%d/status", pids[i]);
            //char state=open(*processPath, O_RDONLY);
            char state=open(*processPath, O_RDONLY);
            if (state == NULL) {
                printf("error!!\n");
                return 0;
            } else {
                printf("State of process with PID : %d is: %c", pids[i], state);
            }

            char *c = (char *) calloc(100, sizeof(char));
            if (state == NULL) {
                perror("r1");
                exit(1);
            }
            char *sz = read(state, c, 10);
            printf("called read(% d, c, 10). returned that"" %d bytes were read.\n", state, *sz);
            c[*sz] = '\0';
            printf("Those bytes are as follows: % s\n", c);

            *processPath = NULL;
            free(*processPath);
        }
    } else {
        printf("Empty process ID list found. Please provide PID to get process info.");
        return 0;
    }

   return 1;
}
//int main(int c, char *args[]) {
//    int pids[] = {13260};
//    getProcessStateByPid(pids);
//    return 0;
//}


