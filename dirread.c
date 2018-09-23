#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int dirRead(int c, char *v[]) {
    DIR *myDirectory;
    struct dirent *myFile;

    printf("c  = %d, v vector = %s\n", c, v[1]);
    if (c == 2) {
        myDirectory = opendir(v[1]);
        if (myDirectory) {
            puts("OK the directory is opened, let's see its files:");
            while ((myFile = readdir(myDirectory)))
                printf("%s\n", myFile->d_name);
            /*
             ** closedir
             */
            if (closedir(myDirectory) == 0)
                puts("The directory is now closed.");
            else
                puts("The directory can not be closed.");
        } else if (errno == ENOENT)
            puts("This directory does not exist.");
        else if (errno == ENOTDIR)
            puts("This file is not a directory.");
        else if (errno == EACCES)
            puts("You do not have the right to open this folder.");
        else
            puts("That's a new error, check the manual.");
    } else
        puts("Sorry we need exactly 2 arguments.");
    return (0);
}
