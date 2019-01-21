/***
 * A simple program to generate ps command
 * Sushma K N <kudlurnirvan@wisc.edu>
 * Srujana <srujana@wisc.edu>
 *
 * This file consist of structures which are used to store process status and option value.
 *
 */
#ifndef OSPROJ_HELPER_H
#define OSPROJ_HELPER_H

typedef struct option_status_value
{
    int updatePstatus;
    int updateUtimeStatus;
    int updateStimeStatus;
    int updateStateStatus;
    int updateCLineStatus;
    int updateVmemoryStatus;
    char* updateOptArgPid;
    char* updateOptArgUtime;
    char* updateOptArgStime;
    char* updateOptArgState;
    char* updateOptArgCLine;
    char* updateOptArgVmemory;
}pDisplay;

typedef struct processInfo{
    int pid;
    char* uTime;
    char* sTime;
    char* vMemory;
    char* cLine;
    char* pState;
}process;

#endif //OSPROJ_HELPER_H
