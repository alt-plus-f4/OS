#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_usage(){
    write(STDOUT_FILENO, "Usage: ./task2 count file.txt\n", 31);
    exit(1);
}

int main(int argc, char const *argv[]){
    if(argc < 2){
        print_usage();
        exit(1);
    }

    for(int i = 0; i < atoi(argv[1]); i++){
        int pid = fork();

        if(pid == 0) {
            execvp(argv[2], (char * const*)&argv[2]);
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
    }


    return 0;
}