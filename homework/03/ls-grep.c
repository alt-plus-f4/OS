#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "grep_file.h"

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
