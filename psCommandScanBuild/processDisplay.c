/***
 * A simple program to generate ps command
 * Srujana <srujana@wisc.edu>
 * Sushma K N <kudlurnirvan@wisc.edu>
 *
 * This file is used to display process info with option list
 *
 */

#ifndef OSPROJ_DISPLAY_C
#define OSPROJ_DISPLAY_C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "processDisplay.h"
#include "processVirtualMemory.h"
#include "processCommandLine.h"
#include "processUtime.h"
#include "processSystime.h"
#include "processState.h"
#include "processUtility.h"
#endif

void displayProcessInfoForSingleProcess(pDisplay display, int pid) {

    process infoList = {pid, NULL, NULL, NULL, NULL,NULL};

    if (display.updateOptArgCLine==0 && display.updateStateStatus==0 && display.updateUtimeStatus==0 && display.updateVmemoryStatus==0 && display.updateStimeStatus==0) {
        infoList.pid = pid;
        infoList.vMemory = getProcessVMUtilisation(pid);
        infoList.cLine = getCommandLineOfProcess(pid);
        infoList.sTime = getProcessSystime(pid);
        infoList.uTime = getProcessUtime(pid);
        infoList.pState = getProcessState(pid);
    } else {
        if ( Opt_Arg_Check(display.updateOptArgPid) == 0) {
            infoList.pid = pid;
        }
        if ( Opt_Arg_Check(display.updateOptArgVmemory) == 1 && display.updateVmemoryStatus==1) {
            infoList.vMemory = getProcessVMUtilisation(pid);
        }
        if ( Opt_Arg_Check(display.updateOptArgCLine) == 1 && display.updateCLineStatus==1) {
            infoList.cLine = getCommandLineOfProcess(pid);
        }
        if (Opt_Arg_Check(display.updateOptArgStime) == 1 && display.updateStimeStatus==1) {
            infoList.sTime = getProcessSystime(pid);
        }
        if (Opt_Arg_Check(display.updateOptArgUtime) == 1 && display.updateUtimeStatus==1) {
            infoList.uTime = getProcessUtime(pid);
        }
        if ( Opt_Arg_Check(display.updateOptArgState) == 1 && display.updateStateStatus==1) {
            infoList.pState = getProcessState(pid);
        }
    }


    printOutput(infoList);
}

void displayProcessInfo(pDisplay display, int pids[]) {

    for (int i = 0; i < 100; i++) {
        if (pids[i] != -1) {
            int pid = pids[i];
            process infoList = {pid, NULL, NULL, NULL, NULL, NULL};
            infoList.pid = pid;
            if (Opt_Arg_Check(display.updateOptArgVmemory) == 1 && display.updateVmemoryStatus == 1) {
                infoList.vMemory = getProcessVMUtilisation(pid);
            }
            if (Opt_Arg_Check(display.updateOptArgCLine) == 1 && display.updateCLineStatus == 1) {
                infoList.cLine = getCommandLineOfProcess(pid);
            }
            if (Opt_Arg_Check(display.updateOptArgStime) == 1 && display.updateStimeStatus == 1) {
                infoList.sTime = getProcessSystime(pid);
            }
            if (Opt_Arg_Check(display.updateOptArgUtime) == 1 && display.updateUtimeStatus == 1) {
                infoList.uTime = getProcessUtime(pid);
            }
            if (Opt_Arg_Check(display.updateOptArgState) == 1 && display.updateStateStatus == 1) {
                infoList.pState = getProcessState(pid);
            }
            if (Opt_Arg_Check(display.updateOptArgPid) == 1 && display.updatePstatus == 1) {
                infoList.vMemory = getProcessVMUtilisation(pid);
                infoList.cLine = getCommandLineOfProcess(pid);
                infoList.sTime = getProcessSystime(pid);
                infoList.pState = getProcessState(pid);
                infoList.uTime = getProcessUtime(pid);
            }
            printOutput(infoList);
        }
    }
}