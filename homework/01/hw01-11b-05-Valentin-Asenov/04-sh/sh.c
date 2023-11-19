#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <stdlib.h>

#define MAX_LINE 80 // 80 chars per command should be enough.

int main(){
    char input[MAX_LINE];
    char *args[MAX_LINE];
    int should_run = 1;

    while(should_run){
        if(!getuid()) printf("root$ ");
        else printf("user$ ");

        fflush(stdout);
        
        fgets(input, MAX_LINE, stdin);
        input[strcspn(input, "\n")] = 0; // Removes enter from input
        
        char *token = strtok(input, " ");
        int i = 0;

        while(token != NULL){
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;

        pid_t pid = fork();
        if(pid < 0){
            fprintf(stderr, "fork: %s\n", strerror(errno));
            continue;
        }

        if(pid == 0){
            if(execvp(args[0], args) < 0)
                fprintf(stderr, "%s: %s\n", args[0], strerror(errno));
            exit(0);
        }

        else wait(NULL);

    }
    
    return 0;
}