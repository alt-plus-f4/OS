#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

void grep_file(const char *search_string, const char *file_name) {
    int pipefd[2];
    pid_t grep_pid;
    
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    grep_pid = fork();
    if (grep_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (grep_pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        execlp("grep", "grep", search_string, file_name, NULL);
        perror("execlp grep");
        exit(EXIT_FAILURE);
    }
    
    close(pipefd[1]);
    
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    
    char line[MAX_STRING_LENGTH];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    
    fclose(fp);
    wait(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <search_string> <file1> [<file2> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    const char *search_string = argv[1];
    
    for (int i = 2; i < argc; ++i) {
        grep_file(search_string, argv[i]);
    }
    
    return 0;
}
