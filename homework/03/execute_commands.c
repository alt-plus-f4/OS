#include "execute_commands.h"

void parse(char *line, char **argv) {
    char *token = strtok(line, " \t\n");
    while (token != NULL) {
        *argv++ = token;
        token = strtok(NULL, " \t\n");
    }
    *argv = '\0';
}

void exec_cmd(char **argv) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    }
    else if (pid == 0) {
        if (execvp(*argv, argv) < 0) {
            perror("exec error");
            exit(1);
        }
    }
    else {
        wait(NULL);
    }
}

void pipe_cmd(char** parsed, char** parsedpipe) { 
    int pipefd[2]; 
    pid_t p1, p2; 

    if (pipe(pipefd) < 0) { 
        perror("Pipe could not be initialized"); 
        return; 
    } 
    p1 = fork(); 
    if (p1 < 0) { 
        perror("Could not fork"); 
        return; 
    } 

    if (p1 == 0) { 
        close(pipefd[0]); 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 

        if (execvp(parsed[0], parsed) < 0) { 
            perror("Could not execute command 1"); 
            exit(0); 
        } 
    } else { 
        p2 = fork(); 

        if (p2 < 0) { 
            perror("Could not fork"); 
            return; 
        } 

        if (p2 == 0) { 
            close(pipefd[1]); 
            dup2(pipefd[0], STDIN_FILENO); 
            close(pipefd[0]); 
            if (execvp(parsedpipe[0], parsedpipe) < 0) { 
                perror("Could not execute command 2"); 
                exit(0); 
            } 
        } 
        else { 
            wait(NULL); 
            wait(NULL); 
        } 
    } 
}