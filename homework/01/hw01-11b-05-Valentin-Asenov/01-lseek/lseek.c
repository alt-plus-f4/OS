#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

typedef struct {
    char data;
    unsigned char nextElementAddress;
} block;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("Usage ./lseek <file>");
        return 1;
    }

    // generate_hidden_file("hidden.hidden");

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    block current_block;
    int offset = 0;

    while (lseek(fd, offset, SEEK_SET) != -1 && read(fd, &current_block, sizeof(block)) > 0) {
        if (current_block.data == 0 || current_block.nextElementAddress == 0) break;

        // printf("%c", current_block.data); //Changed to write
        write(STDOUT_FILENO, &current_block.data, sizeof(char));
        
        offset = current_block.nextElementAddress;
    }

    if (close(fd) == -1) perror("ERROR closing file");

    return 0;
}
