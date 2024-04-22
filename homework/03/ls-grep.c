#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_STRING_LENGTH 100

void ls_grep(const char *search_string, const char **file_names, int num_files) {
    int pipefd[2];
    pid_t cat_pid, grep_pid;
    
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    cat_pid = fork();
    if (cat_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cat_pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        for (int i = 0; i < num_files; ++i) {
            execlp("cat", "cat", file_names[i], NULL);
            perror("execlp cat");
            exit(EXIT_FAILURE);
        }
    }
    
    grep_pid = fork();
    if (grep_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (grep_pid == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        
        execlp("grep", "grep", search_string, NULL);
        perror("execlp grep");
        exit(EXIT_FAILURE);
    }
    
    close(pipefd[0]);
    close(pipefd[1]);
    
    wait(NULL);
    wait(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <search_string> <file1> [<file2> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    const char *search_string = argv[1];
    const char *file_names[MAX_FILES];
    int num_files = argc - 2;
    
    for (int i = 0; i < num_files; ++i) {
        file_names[i] = argv[i + 2];
    }
    
    ls_grep(search_string, file_names, num_files);
    
    return 0;
}
