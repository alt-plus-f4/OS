#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_BUFFER 1024

void* handle_client(void* client_sock) {
    int sock = *(int*)client_sock;
    free(client_sock);

    char filename[MAX_BUFFER];
    if (read(sock, filename, MAX_BUFFER) <= 0) {
        perror("read error");
        close(sock);
        return NULL;
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        const char *message = "Error: file not found\n";
        write(sock, message, strlen(message));
        close(sock);
        printf("Client requested a file not found: %s\n", filename);
        return NULL;
    }

    printf("Sending file: %s\n", filename);

    char buffer[MAX_BUFFER];
    ssize_t numBytes;
    
    while ((numBytes = fread(buffer, sizeof(char), MAX_BUFFER, file)) > 0) {
        if (write(sock, buffer, numBytes) != numBytes) {
            perror("write error");
            break;
        }
    }

    fclose(file);
    close(sock);

    return NULL;
}

int main() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("socket error");
        exit(1);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("bind error");
        exit(1);
    }

    if (listen(server_sock, 5) < 0) {
        perror("listen error");
        exit(1);
    }

    printf("Server listening on port 8080.\n");

    while (1) {
        int *client_sock = malloc(sizeof(int));
        *client_sock = accept(server_sock, NULL, NULL);
        
        if (*client_sock < 0) {
            perror("accept error");
            free(client_sock);
            continue;
        }

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, client_sock) != 0) {
            perror("pthread_create error");
            free(client_sock);
        }
        pthread_detach(thread_id);
    }

    close(server_sock);

    return 0;
}