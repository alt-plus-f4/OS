#include "ls-commands.h"

int main(int argc, char *argv[]) {
    int opt;
    int show_all = 0, long_format = 0, recursive = 0;

    while ((opt = getopt(argc, argv, "AlRar")) != -1) {
        switch (opt) {
            case 'A': show_all = 1; break;
            case 'a': show_all = 1; break;
            case 'l': long_format = 1; break;
            case 'R': recursive = 1; break;
            case 'r': recursive = 1; break;
            default:
                printf("Usage: ./ls [-AlRar] [file...]\n");
                exit(EXIT_FAILURE);
        }
    }

    if (optind == argc) list_dir(".", show_all, long_format, recursive);
    else {
        for (int i = optind; i < argc; i++) {
            struct stat file_stat;
            if (stat(argv[i], &file_stat) == -1) {
                perror("stat err: ");
                continue;
            }

            if (S_ISDIR(file_stat.st_mode)) list_dir(argv[i], show_all, long_format, recursive);
            else formatter(".", argv[i], show_all, long_format, recursive);
        }
    }

    return 0;
}
