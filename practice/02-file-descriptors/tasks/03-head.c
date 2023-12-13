#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void print_usage(){
    write(STDOUT_FILENO, "Usage: ./head <file> [-n count]\n", 32);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 4) print_usage();

    int file = open(argv[1], O_RDONLY);
    if (file == -1) {
        write(STDOUT_FILENO, "Error opening file.\n", 20);
        exit(1);
    }

    if (argc == 4 && strcmp(argv[2], "-n") == 0) {
        int count = atoi(argv[3]);
        char line[256];
        int bytesRead = 0;
        int totalBytesRead = 0;
        while (totalBytesRead < count && (bytesRead = read(file, line, sizeof(line))) > 0) {
            write(STDOUT_FILENO, line, bytesRead);
            totalBytesRead += bytesRead;
        }
    }
    else {
        char line[256];
        int lineCount = 0;
        int bytesRead = 0;
        int totalBytesRead = 0;
        while (lineCount < 10 && (bytesRead = read(file, line, sizeof(line))) > 0) {
            write(STDOUT_FILENO, line, bytesRead);
            totalBytesRead += bytesRead;
            for (int i = 0; i < bytesRead; i++) {
                if (line[i] == '\n') {
                    lineCount++;
                    if (lineCount == 10) {
                        break;
                    }
                }
            }
        }
    }

    close(file);
    return 0;
}