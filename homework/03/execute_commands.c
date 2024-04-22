#include "execute_commands.h"

void parse(char *line, char **argv) {
    while (*line != '\0') {
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';
        *argv++ = line;
        while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n') 
            line++;
    }
    *argv = '\0';
}

void exec_cmd(char **argv) {
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(1);
    }
    else if (pid == 0) {
        if (execvp(*argv, argv) < 0) {
            printf("exec error\n");
            exit(1);
        }
    }
    else {
        while (wait(&status) != pid);
    }
}

void pipe_cmd(char **argv, char **argv2) {
    int pipefd[2];
    pid_t p1, p2;

    if (pipe(pipefd) < 0) {
        printf("pipe error\n");
        exit(1);
    }
    
    p1 = fork();
    if (p1 < 0) {
        printf("fork error\n");
        exit(1);
    }

    if (p1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        if (execvp(argv[0], argv) < 0) {
            printf("exec error\n");
            exit(1);
        }    
    }
    else {
        p2 = fork();

        if (p2 < 0) {
            printf("fork error\n");
            exit(1);
        }


        if (p2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);

            if (execvp(argv2[0], argv2) < 0) {
                printf("exec error\n");
                exit(1);
            }
        }
        else {
            close(pipefd[1]);
            wait(NULL);
            wait(NULL);
        }
    }
}