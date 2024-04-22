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
    char *argv[MAX_LINE];
    char *argv2[MAX_LINE];

    while (1) {
        printf("%s$ ", getuid() ? "user" : "root");
        fflush(stdout);

        fgets(line, MAX_LINE, stdin);
        line[strcspn(line, "\n")] = 0;

        parse(line, argv);

        if (strcmp(argv[0], "exit") == 0)
            exit(0);

        int i = 0;
        while (argv[i] != NULL) {
            if (strcmp(argv[i], "|") == 0) {
                argv[i] = NULL;
                int j = 0;
                while (argv[i + j + 1] != NULL) {
                    argv2[j] = argv[i + j + 1];
                    j++;
                }
                argv2[j] = NULL;
                pipe_cmd(argv, argv2);
                break;
            }
            i++;
        }
        if (argv[i] == NULL) {
            pid_t pid = fork();
            if (pid < 0) {
                printf("Fork error\n");
                exit(1);
            } else if (pid == 0) {
                exec_cmd(argv);
            } else {
                wait(NULL);
                memset(line, 0, sizeof(line));
            }
        }
    }

    return 0;
}
