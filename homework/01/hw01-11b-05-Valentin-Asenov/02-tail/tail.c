#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 

int main(int argc, char const *argv[]){
    if(argc < 2) {
        perror("Usage: tail <files[]>");
        return 1;
    }

    for(int i = 1; i < argc; i++){
        struct stat st;

        //* Checks

        if(stat(argv[i], &st) == -1) {
            perror("Unable to stat file");
            return 1;
        }

        if(S_ISDIR(st.st_mode)) {
            fprintf(stderr, "./tail: perror reading '%s': Is a directory\n", argv[i]);
            return 1;
        }

        int fp = open(argv[i], O_RDONLY);
        if(fp == -1) {
            perror("Unable to open file");
            return 1;
        }

        printf("\n==> %s <==\n", argv[i]);

        //* Actual code:

        lseek(fp, 0, SEEK_END);
        lseek(fp, -1, SEEK_CUR);

        char buffer;
        int numberOfLines = 0;

        // if there is an error with read, if 10 lines have been
        // read or if the beginning of the file has been reached 
        
        while(read(fp, &buffer, 1) > 0 && numberOfLines < 10 && lseek(fp, -2, SEEK_CUR) != -1) 
            if(buffer == '\n') numberOfLines++;

        while(read(fp, &buffer, 1) > 0)
            write(STDOUT_FILENO, &buffer, 1);
    
       if(close(fp) != 0) perror("Unable to close file. ERROR:");
    }

    return 0;
}