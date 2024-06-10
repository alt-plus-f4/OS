#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <errno.h>

void list_directory(const char *dir_name, int show_all, int long_format, int recursive);
void print_file_info(struct stat *file_stat, const char *file_name);
void process_entry(const char *path, const char *name, int show_all, int long_format, int recursive);