#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER 1024
#define DEFAULT_FILENAME "image.png"
#define ERROR_PREFIX "Error:"

int main(int argc, char const *argv[]) {
    const char *filename = (argc == 2) ? argv[1] : DEFAULT_FILENAME;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket error");
        exit(1);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("inet_pton error");
        exit(1);
    }

    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("connect error");
        exit(1);
    }

    if (write(sock, filename, strlen(filename) + 1) == -1) {
        perror("write error");
        exit(1);
    }

    char buffer[MAX_BUFFER];
    ssize_t numBytes = read(sock, buffer, MAX_BUFFER);
    if (numBytes > 0) {
        buffer[numBytes] = '\0';
        if (strncmp(buffer, ERROR_PREFIX, strlen(ERROR_PREFIX)) == 0) {
            printf("Server responded with error: %s\n", buffer);
            close(sock);
            exit(1);
        }
    } else if (numBytes < 0) {
        perror("read error");
        exit(1);
    }

    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("fopen error");
        exit(1);
    }

    fwrite(buffer, sizeof(char), numBytes, file);

    while ((numBytes = read(sock, buffer, MAX_BUFFER)) > 0)
        fwrite(buffer, sizeof(char), numBytes, file);

    if (numBytes < 0) perror("read error");
    else printf("File %s received successfully.\n", filename);

    fclose(file);
    close(sock);

    return 0;
}