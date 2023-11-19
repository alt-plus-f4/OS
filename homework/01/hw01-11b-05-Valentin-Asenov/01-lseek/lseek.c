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

void generate_hidden_file(const char *filename) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    srand(time(NULL));
    block current_block;

    char string[] = "I like G2"; // :)))
    int string_length = strlen(string);

    printf("Sting length: %d\n", string_length);

    off_t offset = 0;

    for (int i = 0; i < string_length; ++i) {
        current_block.data = string[i];
        current_block.nextElementAddress = (i == string_length) ? 0 : offset + sizeof(block);

        if (write(fd, &current_block, sizeof(block)) == -1) {
            perror("write");
            close(fd);
            exit(1);
        }

        offset = current_block.nextElementAddress;
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
}

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

        printf("%c", current_block.data);
        
        offset = current_block.nextElementAddress;
    }

    if (close(fd) == -1) perror("ERROR closing file");

    return 0;
}
