#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <fcntl.h>

#define MAX_CHARS 100
#define MAX_STRING_LENGTH 512
#define error(msg) { perror(msg); exit(1); }

void execute_single(char* argv){
    pid_t pid = fork();

    if (pid < 0) error("fork err")
    else if (pid == 0) {
        if (execvp(argv, NULL) < 0) error("Exec Err")
        exit(0);
    } 
    else wait(NULL);
}

void execute_piped(char* filename){
    printf("Command executed now type another command: \n");
    fflush(stdout);

    char* command = malloc(MAX_CHARS);
    scanf("%s", command);
    fflush(stdout);
    
    int pipefd[2];
    pid_t command_pid;
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if(fd == -1) error("Unable to open file")
    
    if (pipe(pipefd) == -1) error("pipe error")
    
    command_pid = fork();
    if (command_pid == -1) error("fork error")
    if (command_pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        execvp(command, NULL);
        error("command exec error")
    }
    
    close(pipefd[1]);
    char line[MAX_STRING_LENGTH];
    while (read(pipefd[0], line, MAX_STRING_LENGTH) > 0);
    
    // printf("LINE: %s\nASD", line);
    // printf("Line len: %d\n", strlen(line)); 
    write(fd, line, strlen(line));
    
    close(pipefd[0]);
    close(fd);
    wait(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 3) error("Usage ./dump-to-file <command> <filename>")
    
    // for(int i = 0; i < argc; i++)
    //     printf("%s\n", argv[i]);

    execute_single(argv[1]);
    execute_piped(argv[2]);

    printf("Done.\n");

    return 0;
}