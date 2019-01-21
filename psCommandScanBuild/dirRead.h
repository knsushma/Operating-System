/***
 * A simple program to generate ps command
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * This file will list all process ID's
 *
 */
#ifndef OSPROJ_PARSECOMMAND_H
#define OSPROJ_PARSECOMMAND_H

int dirRead(int c, char *args[]);
char * getProcPathName(int pid);
int isUserIdMatching(char *line);
char* accessValidatePid(int pid);
#endif