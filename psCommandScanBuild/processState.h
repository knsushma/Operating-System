/***
 * A simple program to generate ps command
 * Srujana <srujana@wisc.edu>
 * Sushma K N <kudlurnirvan@wisc.edu>
 *
 * This file is used to fetch process state information based on processID
 *
 */
#ifndef OSPROJ_PSTATE_H
#define OSPROJ_PSTATE_H

char * getProcessState(int pid);
char * getProcStatPathName(int pid);

#endif