#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 
#include <stdlib.h>

#define MAX_CHARS 256

void print_usage(){
    write(STDOUT_FILENO, "Usage: ./head <files>\n", 23);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) print_usage();

    int file = open(argv[1], O_RDONLY);
    if (file == -1) {
        perror("cannot open file for reading: ");
        exit(1);
    }

    for(int i = 1; i < argc; i++){
        struct stat st;

        if(stat(argv[i], &st) == -1) {
            perror("Unable to open file");
            return 1;
        }

        if(S_ISDIR(st.st_mode)) {
            fprintf(stderr, "./head: perror reading '%s': Is a directory\n", argv[i]);
            return 1;
        }

        int fp = open(argv[i], O_RDONLY);
        if(fp == -1) {
            perror("Unable to open file");
            return 1;
        }

        printf("%s\n", argv[i]);

        int numberOfLines = 0;
        char buffer;

        while(read(fp, &buffer, 1) > 0){
            if (buffer == '\n') {
                numberOfLines++;
                if (numberOfLines == 10) break;
            }
            write(STDOUT_FILENO, &buffer, 1);
        }
    
       if(close(fp) != 0) perror("Unable to close file. ERROR:");
    }


    close(file);
    return 0;
}