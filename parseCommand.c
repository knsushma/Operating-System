#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "processVirMemory.h"
#include "processCommandLine.h"
int parseCommand(int argc, char *argv[],int pids[])
{
    int flags, opt;
    int nsecs, tfnd;
    nsecs = 0;
    tfnd = 0;
    flags = 0;
    while ((opt = getopt(argc, argv, "p:s::U::v::c::S::")) != -1) {
        switch (opt) {
            case 'v':
                flags = 1;
                printf("inside -v:\n");
                getProcessVirtualMemory(pids);
                break;
            case 'c':
                flags = 1;
                printf("inside -c:\n");
                getCommandLineOfProc(pids);
                break;
            case 't':
                nsecs = atoi(optarg);
                tfnd = 1;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
                //exit(EXIT_FAILURE);
        }
    }
    printf("flags=%d; tfnd=%d; nsecs=%d; optind=%d\n", flags, tfnd, nsecs, optind);
    if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        //exit(EXIT_FAILURE);
        return -1;
    }
    printf("name argument = %s\n", argv[optind]);
    /* Other code omitted */
    //exit(EXIT_SUCCESS);
    return -1;
}



//int main(int c, char *args[]) {
//    int pids[] = {3116};
//    parseCommand(c,args,pids);
//    getVirtualMemoryOfProc(c, args, pids);
//    return 1;
//}

////////////////////////////////////////////////

//#include <unistd.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include "parseCommand.h"
//
//int parseCommand(int argc, char *argv[])
// {
//    int flags, opt;
//    int nsecs, tfnd;
//    nsecs = 0;
//    tfnd = 0;
//    flags = 0;
//    while ((opt = getopt(argc, argv, "nt:")) != -1) {
//           switch (opt) {
//               case 'n':
//                       flags = 1;
//                     break;
//               case 't':
//                     nsecs = atoi(optarg);
//                     tfnd = 1;
//                     break;
//               default: /* '?' */
//                     fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
//                         }
//        }
//   printf("flags=%d; tfnd=%d; nsecs=%d; optind=%d\n", flags, tfnd, nsecs, optind);
//    if (optind >= argc) {
//       fprintf(stderr, "Expected argument after options\n");
//               }
//   printf("name argument = %s\n", argv[optind]);
//   /* Other code omitted */
//}
//
