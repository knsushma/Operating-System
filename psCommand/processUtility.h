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
char * tokenizeString(char *inputString, char *delimiter);
char * getSpecificTokenInString(char *inputString, char * delimiters, int tokenNumber);
int cmpfunc (const void * a, const void * b);
char* read_file(char directory_name[], char file_name[]);
int isPidMentioned(int count, char *args[]);
char * getFilePath(char directory_name[],int pid, char file_name[], char *filePath);
char * remove_spaces(const char *input);
void printOutput(process p);
int Opt_Arg_Check(char * optargs);

#endif