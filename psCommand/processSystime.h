/***
 * A simple program to generate ps command
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * This file is used to fetch process system time information based on processID
 *
 */
#ifndef OSPROJ_PSTIME_H
#define OSPROJ_PSTIME_H

char * getProcessSystime(int pid);
char * getProcSystimePathName(int pid);

#endif