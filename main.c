#include <stdio.h>
#include "dirRead.h"
#include "parseCommand.h"

int mains(int c, char *args[]) {
    printf("argument list:  %s\n", args[1]);
    printf("Hello, World!\n");
    //parseCommand(c, args);
    dirRead(c, args);
    return 0;
}
