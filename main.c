#include <stdio.h>
#include "dirread.h"

int main(int c, char *args[]) {
    printf("argument list:  %s\n", args[1]);
    printf("Hello, World!\n");
    dirRead(c, args);
    return 0;
}