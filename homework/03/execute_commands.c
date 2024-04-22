#include "execute_commands.h"

void parse(char *line, char **argv) {
    char *token = strtok(line, " \t\n");
    while (token != NULL) {
        *argv++ = token;
        token = strtok(NULL, " \t\n");
    }
    *argv = NULL;
}

void exec_cmd(char **argv) {
    if (execvp(*argv, argv) < 0) {
        perror("exec error");
        exit(EXIT_FAILURE);
    }
}

void execute_commands(char **commands) {
    int pipefd[2];
    pid_t pid;
    int fd_in = 0;

    while (*commands != NULL) {
        if (pipe(pipefd) < 0) {
            perror("pipe error");
            exit(EXIT_FAILURE);
        }

        if ((pid = fork()) == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            dup2(fd_in, STDIN_FILENO);
            if (*(commands + 1) != NULL) {
                dup2(pipefd[1], STDOUT_FILENO);
            }
            close(pipefd[0]);
            exec_cmd(commands);
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
            close(pipefd[1]);
            fd_in = pipefd[0];
            commands++;
        }
    }
}