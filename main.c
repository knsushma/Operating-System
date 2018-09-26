#include <stdio.h>
#include "parseCommand.h"
#include "dirRead.h"
#include "processCommandLine.h"
#include "processInfoByPid.h"
#include "processStateByPid.h"
#include "processSystime.h"
#include "processUtime.h"
#include "processVirMemory.h"

int main(int c, char *args[]) {
    int pids[] = {1745};
    printf("argument list:  %s\n", args[1]);
    printf("Hello, World!\n");
    parseCommand(c, args);
    dirRead(c, args);
    getCommandLineOfProc(pids);
    getProcessInfoByPid(pids);
    getProcessStateByPid(pids);
    getProcessSystime(pids);
    getProcessUtime(pids);
    getProcessVirtualMemory(pids);
    return 0;
}
