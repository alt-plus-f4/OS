#include "execute_commands.h"

#define MAX_LINE 80

void parse(char *line, char **argv) {
    char *token = strtok(line, " \t\n");
    if (token == NULL) return;
    *argv++ = token;
    while ((token = strtok(NULL, " \t\n")) != NULL)
        *argv++ = token;
    *argv = NULL;
}

void parse_commands(char *line, char **commands) {
    char *token = strtok(line, "|");
    int i = 0;
    while (token != NULL) {
        commands[i++] = token;
        token = strtok(NULL, "|");
    }
    commands[i] = NULL;
}

void exec_cmd(char **argv) {
    execvp(argv[0], argv);
    perror("exec error");
    exit(EXIT_FAILURE);
}

void execute_commands(char **commands) {
    int num_pipes = 0;
    char *cmd[MAX_LINE];

    while (commands[num_pipes] != NULL) {
        num_pipes++;
    }

    int pipefd[num_pipes - 1][2];

    for (int i = 0; i < num_pipes - 1; i++) {
        if (pipe(pipefd[i]) < 0) {
            perror("pipe error");
            exit(EXIT_FAILURE);
        }
    }

    int fd_in = STDIN_FILENO;
    for (int i = 0; i < num_pipes; i++) {
        parse(commands[i], cmd);
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (i > 0) {
                dup2(pipefd[i - 1][0], STDIN_FILENO);
                close(pipefd[i - 1][1]);
            } else {
                dup2(fd_in, STDIN_FILENO);
            }

            if (i < num_pipes - 1) {
                dup2(pipefd[i][1], STDOUT_FILENO);
            }

            for (int j = 0; j < num_pipes - 1; j++) {
                close(pipefd[j][0]);
                close(pipefd[j][1]);
            }

            exec_cmd(cmd);
            exit(EXIT_FAILURE);
        }

        if (i > 0) {
            close(pipefd[i - 1][0]);
            close(pipefd[i - 1][1]);
        }
    }

    for (int i = 0; i < num_pipes - 1; i++) {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
    }

    for (int i = 0; i < num_pipes; i++) {
        wait(NULL);
    }
}
