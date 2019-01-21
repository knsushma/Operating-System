/***
 * A simple program to generate ps command
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * Main function to trigger ps command
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ps537Handler.h"


int main(int c, char *args[]) {

    printf("args: %d \t %s \t %s \n", c, args[0], args[1]);
    execute537PSCommand(c, args);

    return 1;
}
