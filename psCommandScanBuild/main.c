

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

    execute537PSCommand(c, args);

    return 1;
}
