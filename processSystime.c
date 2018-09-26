#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
int systime(int c, char *v[], int pids[])
{
    struct stat *buf;

    printf("Inside system time command");
    if(sizeof(pids)>0) {
        for (int i = 0; i < sizeof(pids) / sizeof(int); i++) {

            printf("i value: %d",i);

            char *filePath;
            asprintf(&filePath, "/proc/%c/stat/stime", pids[i]);

            printf("filePath to check \"%s\"\n",filePath);

            int cLarg = open(filePath, O_RDONLY);
            if (cLarg < 0) {
                printf("error!!\n");
                exit(1);
            } else {
                printf("systime=%d\n", cLarg);
                char *c = (char *) calloc(100, sizeof(char));
                int sz = read(cLarg, c, 10);
                printf("called read(% d, c, 10). returned that" " %d bytes were read.\n", cLarg, sz);
                c[sz] = '\0';
                printf("Those bytes are as follows: % s\n", c);
            }
            *filePath = NULL;
            free(*filePath);
        }
    }

       return 1;
}
