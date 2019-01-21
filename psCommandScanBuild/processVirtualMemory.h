/***
 * A simple program to generate ps command
 * Srujana <srujana@wisc.edu>
 * Sushma K N <kudlurnirvan@wisc.edu>
 * This file is used to fetch virtual memory consumed by a process based on processID
 *
 */
#ifndef OSPROJ_PVIRTUAL_H
#define OSPROJ_PVIRTUAL_H

char * getProcessVMUtilisation(int pid);
char * getProcVMPathName(int pid);

#endif