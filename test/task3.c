#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_usage(){
    write(STDOUT_FILENO, "Usage: ./task3 file1 file2 file3 command\n", 42);
    exit(1);
}

int open_file(char const *filename){
    int fd = open(filename, O_CREAT| O_WRONLY, 0644);
    if (fd == -1) {
        perror("cannot open file for writing: ");
        exit(1);
    }
    return fd;
}

int main(int argc, char const *argv[]){
    if(argc < 5){
        print_usage();
        exit(1);
    }

    int fd = open_file(argv[1]);
    write(fd, "Nice args\n", 10);
    close(fd);

    fd = open_file(argv[2]);

    int pid = fork();
    int return_status = 0;
    
    if(pid == 0) return_status = execlp(argv[4], argv[4], NULL);
    else if(pid == -1){
        perror("Unable to fork");
        return 1;
    }
    else waitpid(pid, NULL, 0);

    if(!return_status) write(fd, "0\n", 2);
    else write(fd, "ERROR\n", 6);
    close(fd);

    if(execlp("cp", "cp", argv[2], argv[3], NULL) != 0)
        perror("CP error: ");

    return 0;
}
