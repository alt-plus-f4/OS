#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 

#define MAX_CHARS 128

typedef struct{
    char data;
    unsigned char nextElementAddress;
} block;

int main(int argc, char const *argv[]){
    if(argc < 2) {
        perror("Usage: lseek <file>");
        return 1;
    }

    int fp = open(argv[1], O_RDONLY);
    if(fp == -1) {
        perror("Unable to open file");
        return 1;
    }

    block blocks[MAX_CHARS];
    ssize_t bytesRead;
    int i;

    for(i = 0; i < MAX_CHARS; i++){
        bytesRead = read(fp, &blocks[i].data, 1);
        
        if(bytesRead <= 0) {
            blocks[i].nextElementAddress = 0;
            break;
        }
        
        blocks[i].nextElementAddress = i == 127 ? 0 : i; 
    }

    if(close(fp) != 0) perror("Unable to close file. ERROR:");

    for(int j = 0; j < i; j++)
        write(STDOUT_FILENO, &blocks[j].data, 1);
    
    return 0;
}