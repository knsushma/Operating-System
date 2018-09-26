//
// Created by Sushma K N on 23/09/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "processUtime.h"

//#include <readline/readline.h>
//#include <readline/history.h>

int getPidsByUserId() {

}

//char * readSpecificLineFromFile(char *filePath, int readline) {
//    FILE *stream;
//    char line[256];
//    int count = 0;
//    char *data;
//
//    stream = fopen(filePath, "r");
//    while (fgets(line, sizeof(line), stream)) {
//        count++;
//        if (count == readline) {
//            printf("%s", line);
//            data = line;
//        }
//    }
//
//    return data;
//
//}


//int fileRead(char *filename) {
//    FILE *stream;
//    char *line = NULL;
//    size_t len = 0;
//    ssize_t nread;
//    int count = 0;
//
//    stream = fopen(filename, "r");
//    if (stream == NULL) {
//        perror("fopen");
//        exit(EXIT_FAILURE);
//    }
//
//    while ((nread = getline(&line, &len, stream)) != -1) {
//        //printf("Retrieved line of length %zu:\n", nread);
//        //fwrite(line, nread, 1, stdout);
//        fwrite(line, nread, 1, stdout);
//        count++;
//    }
//
//    free(line);
//    fclose(stream);
//    exit(EXIT_SUCCESS);
//
//    return 1;
//}

//int main() {
//
//}
