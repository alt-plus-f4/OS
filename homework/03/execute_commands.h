#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <stdlib.h>

void parse(char *line, char **argv);
void exec_cmd(char **argv);
void pipe_cmd(char** parsed, char** parsedpipe);