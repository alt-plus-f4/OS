#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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