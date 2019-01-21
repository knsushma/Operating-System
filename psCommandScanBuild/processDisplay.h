/***
 * A simple program to generate ps command
 * Srujana <srujana@wisc.edu>
 * Sushma K N <kudlurnirvan@wisc.edu>
 *
 * This file is used to display process info based on process ID
 *
 */
#ifndef OSPROJ_DISPLAY_H
#define OSPROJ_DISPLAY_H

#include "helper.h"

void displayProcessInfo(pDisplay display, int pids[]);
void displayProcessInfoForSingleProcess(pDisplay display, int pid);
#endif



