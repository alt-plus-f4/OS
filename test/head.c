#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_CHARS 256

void print_usage(){
    write(STDOUT_FILENO, "Usage: ./head <file> [-n count]\n", 32);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 4) print_usage();

    int file = open(argv[1], O_RDONLY);
    if (file == -1) {
        perror("cannot open file for reading: ");
        exit(1);
    }

    if (argc == 4 && strcmp(argv[2], "-n") == 0) {
        int count = atoi(argv[3]);
        char line[MAX_CHARS];
        int bytesRead = 0;
        int totalBytesRead = 0;
        while (totalBytesRead < count && (bytesRead = read(file, line, sizeof(line))) > 0) {
            write(STDOUT_FILENO, line, bytesRead);
            totalBytesRead += bytesRead;
        }
    }
    else {
        char line[MAX_CHARS];
        int lineCount = 0, bytesRead = 0, totalBytesRead = 0;
        while (lineCount < 10 && (bytesRead = read(file, line, sizeof(line))) > 0) {
            write(STDOUT_FILENO, line, bytesRead);
            totalBytesRead += bytesRead;
            for (int i = 0; i < bytesRead; i++) {
                if (line[i] == '\n') {
                    lineCount++;
                    if (lineCount == 10) break;
                }
            }
        }
    }

    close(file);
    return 0;
}