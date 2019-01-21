/***
 * A simple program to generate ps command
 * Srujana <srujana@wisc.edu>
 * Sushma K N <kudlurnirvan@wisc.edu>
 *
 * This file is used to fetch command line details which triggered the respective process based on processID
 *
 */
#ifndef OSPROJ_COMMANDLINE_H
#define OSPROJ_COMMANDLINE_H

char * getCommandLineOfProcess(int pid);
char * getProcCmdLinePathName(int pid);

#endif