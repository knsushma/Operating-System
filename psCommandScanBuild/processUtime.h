/***
 * A simple program to generate ps command
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * This file is used to fetch process user time information based on processID
 *
 */
#ifndef OSPROJ_UTIME_H
#define OSPROJ_UTIME_H

char * getProcessUtime(int pid);
char * getProcUtimePathName(int pid);

#endif