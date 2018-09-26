#include <stdio.h>
#include "dirRead.h"
#include "parseCommand.h"
#include "processCommandLine.h"
#include "processVirMemory.h"
#include "processSystime.h"

int mains(int c, char *args[]) {
    printf("argument list:  %s\n", args[1]);
    printf("Hello, World!\n");
    int pids = parseCommand(c, args);
//    dirRead(c, args);
//    commandLine(c, args, pids);
//    VirMemory(c,args, pids);
//    systime(c,args, pids);
    return 0;
}
