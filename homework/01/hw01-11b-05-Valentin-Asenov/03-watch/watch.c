#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 

int main(int argc, char const *argv[]){
    if(argc < 2){ 
        perror("Usage: watch <command> <optional: arguments>");
        return 1;
    }

    while(1){
        int pid = fork();

        if(pid == 0) {
            execvp(argv[1], (char * const*)&argv[1]);
            perror("Unable to execute command");
            _exit(1);
        }
        
        else if(pid == -1) {
            perror("Unable to fork");
            return 1;
        }
        
        else {
            int status;
            waitpid(pid, &status, 0);
        }

        sleep(2);
    }

    return 0;
}