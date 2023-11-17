#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 

#define MAX_CHARS 128

int main(int argc, char const *argv[]){
    if(argc < 2) {
        perror("Usage: tail <files[]>");
        return -1;
    }

    for(int i = 1; i < argc; i++){
        struct stat st;

        if(stat(argv[i], &st) != 0) {
            perror("Unable to open file");
            continue;
        }

        if(S_ISDIR(st.st_mode)) {
            fprintf(stderr, "./tail: perror reading '%s': Is a directory\n", argv[i]);
            continue;
        }

        int fp = open(argv[i], O_RDONLY);
        if(fp == -1) {
            perror("Unable to open file");
            continue;
        }
        
        char buffer[MAX_CHARS]; 
        ssize_t bytesRead = read(fp, buffer, MAX_CHARS);

        if(bytesRead > 0) {
            if(argc > 2) printf("==> %s <==\n", argv[i]);
            write(STDOUT_FILENO, buffer, bytesRead);
            puts("\n");
        }
        
       if(close(fp) != 0) perror("Unable to close file. ERROR:");
    }

    return 0;
}