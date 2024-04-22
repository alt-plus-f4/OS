#include "grep_file.h"

#define MAX_STRING_LENGTH 100
#define error(msg) { perror(msg); exit(1); }

void grep_file(const char *search_string, const char *file_name) {
    int pipefd[2];
    pid_t grep_pid;
    
    if (pipe(pipefd) == -1) error("pipe error");
    
    grep_pid = fork();
    if (grep_pid == -1) error("fork error");
    if (grep_pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        execlp("grep", "grep", search_string, file_name, NULL);
        error("grep exec error");
    }
    
    close(pipefd[1]);
    
    char line[MAX_STRING_LENGTH];
    while (read(pipefd[0], line, MAX_STRING_LENGTH) > 0) printf("%s", line);
    
    close(pipefd[0]);
    wait(NULL);
}
