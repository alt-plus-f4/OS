#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 

#include "vector/vector.h"

int main(int argc, char const *argv[]){
    if(argc < 2){ 
        perror("Usage: watch <command> <optional: arguments>");
        return 1;
    }

    while(1){
        int pid = fork();

        if(pid == 0) {
            vector_t *args = vector_init();

            vector_push(args, (void*)argv[1]);

            for(int i = 2; i < argc; i++)
                vector_push(args, (void*)argv[i]);     

            vector_push(args, NULL);
            char **argList = (char**) vector_getall(args);
            
            execvp(argv[1], argList);

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

// Вектора го писахме миналата година, не съм преписвал..