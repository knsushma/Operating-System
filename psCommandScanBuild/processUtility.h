/***
 * A simple program to generate ps command
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * It is a Utility file which includes definitions of functions which are generic and used accross multiple files.
 *
 */
#ifndef OSPROJ_PUTILITY_H
#define OSPROJ_PUTILITY_H

#include "helper.h"

char * readSpecificLineFromFile(char *filePath, int readLine);
int cmpfunc (const void * a, const void * b);
char * remove_spaces(const char *input);
void printOutput(process p);
int Opt_Arg_Check(char * optargs);

#endif