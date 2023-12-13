#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./cp <source_file> <destination_file>\n");
        return 1;
    }

    int source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1) {
        printf("Error opening source file.\n");
        return 1;
    }

    int destination_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destination_fd == -1) {
        printf("Error opening destination file.\n");
        close(source_fd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(destination_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            printf("Error writing to destination file.\n");
            close(source_fd);
            close(destination_fd);
            return 1;
        }
    }

    close(source_fd);
    close(destination_fd);

    printf("File copied successfully.\n");

    return 0;
}