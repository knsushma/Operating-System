#include <stdio.h>
#include "parseCommand.h"
#include "dirRead.h"
#include "processCommandLine.h"
#include "processInfoByPid.h"
#include "processStateByPid.h"
#include "processSystime.h"
#include "processUtime.h"
#include "processVirMemory.h"
#include "processUtility.h"

int main(int c, char *args[]) {
    int pids[] = {1745};
    printf("argument list:  %s\n", args[1]);
    printf("Hello, World!\n");

    if (c == 1 || (c ==2 && processMentioned(args)==0)) {
        dirRead(c, args);
    }

    parseCommand(c, args, pids);
    getCommandLineOfProc(pids);
    getProcessInfoByPid(pids);
    getProcessStateByPid(pids);
    getProcessSystime(pids);
    getProcessUtime(pids);
    getProcessVirtualMemory(pids);
    return 0;
}
