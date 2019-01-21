/***
 * A simple program to generate ps command
 * Srujana <srujana@wisc.edu>
 * Sushma K N <kudlurnirvan@wisc.edu>
 *
 * This file is used to parse and validate all command line arguments
 *
 */
#ifndef OSPROJ_PARSECOMMAND_C
#define OSPROJ_PARSECOMMAND_C

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stddef.h>
#include "processDisplay.h"
#include "parseCommand.h"
#include "processUtility.h"

int parseCommand(int argc, char *argv[],int pids[]) {

    int opt;
    int pFlag=0;

    if (argc >1) {
        pDisplay status_op = {0,0,0,0,0,0, NULL,NULL,NULL,NULL,NULL,NULL};


        while ((opt = getopt(argc, argv, "p:s::U::v::c::S::")) != -1) {
            switch (opt) {
                case 'v':
                    status_op.updateOptArgVmemory = optarg;
                    status_op.updateVmemoryStatus = 1;
                    break;
                case 'c':
                    status_op.updateOptArgCLine = optarg;
                    status_op.updateCLineStatus = 1;
                    break;
                case 'S':
                    status_op.updateOptArgStime = optarg;
                    status_op.updateStimeStatus = 1;
                    break;
                case 's':
                    status_op.updateOptArgState = optarg;
                    status_op.updateStateStatus = 1;

                    break;
                case 'U':
                    status_op.updateOptArgUtime = optarg;
                    status_op.updateUtimeStatus = 1;

                    break;
                case 'p':
                    status_op.updateOptArgPid = optarg;
                    if(Opt_Arg_Check(status_op.updateOptArgPid)==1)
                    {
                        printf("Enter a valid argument -p<pid> -s -U -S -v -c\n");
                        exit(1);
                    }
                    status_op.updatePstatus = 1;
                    pFlag=1;
                    break;
                default: /* '?' */
                    printf("Enter a valid argument -p<pid> -s -U -S -v -c\n");
                    exit(1);
                    break;
            }
        }
        if (optind >= argc && argc<2) {
            fprintf(stderr, "Expected argument after options\n");
            return -1;
        }
        else if(argc>optind)
        {
            fprintf(stderr, "Arguments have more options\nEnter a valid argument -p<pid> -s -U -S -v -c\n");
            return -1;
        }
        if(pFlag==1)
        {
            int procID=atoi(status_op.updateOptArgPid);
            displayProcessInfoForSingleProcess(status_op,procID);
        }
        else
        {
            displayProcessInfo(status_op, pids);
        }
    } else if ( argc == 1) {
        pDisplay status_op = {1,1,1,1,1,1, NULL,NULL,NULL,NULL,NULL,NULL};
        displayProcessInfo(status_op, pids);
    }
    return -1;
}

#endif