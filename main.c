#include <stdio.h>
#include "dirRead.h"
#include "parseCommand.h"
#include "commandLine.h"

int main(int c, char *args[]) {
    printf("argument list:  %s\n", args[1]);
    printf("Hello, World!\n");
//    parseCommand(c, args);
    dirRead(c, args);
    commandLine(c, args);
    VirMemory(c,args);
    parseCommand(c, args);
    return 0;
}
