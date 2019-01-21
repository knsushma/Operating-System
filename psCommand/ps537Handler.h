/***
 * A simple program to generate ps command
 * Srujana <srujana@wisc.edu>
 * Sushma K N <kudlurnirvan@wisc.edu>
 * This file is used to handle errors in process status command input
 *
 */
#ifndef OSPROJ_UTIME_H
#define OSPROJ_UTIME_H
void execute537PSCommand(int c, char *args[]);
char * getOtherPartOfSubstring(char *inputString);
void validatePidAndCallParser(int argCount, char *args[], char *pid);
void validateForRestCLI(int argCount, char *args[], int start, char *subString);
char * validateForPid(int argCount, char *args[], int i, char *subString);
#endif