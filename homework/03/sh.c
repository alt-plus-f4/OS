#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include "execute_commands.h"

#define MAX_LINE 80

int main() {
    char line[MAX_LINE];
    char *commands[MAX_LINE];

    while (1) {
        printf("%s$ ", getuid() ? "user" : "root");
        fflush(stdout);

        fgets(line, MAX_LINE, stdin);
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, "|");
        int i = 0;
        while (token != NULL) {
            commands[i++] = token;
            token = strtok(NULL, "|");
        }
        commands[i] = NULL;

        execute_commands(commands);
    }

    return 0;
}