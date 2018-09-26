#include <stdio.h>
#include "dirRead.h"
#include "parseCommand.h"
#include "commandLine.h"
#include "VirMemory.h"
#include "systime.h"

int mains(int c, char *args[]) {
    printf("argument list:  %s\n", args[1]);
    printf("Hello, World!\n");
//    parseCommand(c, args);
//    systime(c,args);
    dirRead(c, args);
    commandLine(c, args);
    VirMemory(c,args);
    systime(c,args);
    parseCommand(c, args);
    return 0;
}
