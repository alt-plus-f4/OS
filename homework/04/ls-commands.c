#include "ls-commands.h"

void print_file_info(struct stat *file_stat, const char *file_name) {
    char permissions[11] = "----------";
    if (S_ISDIR(file_stat->st_mode)) permissions[0] = 'd';
    if (S_ISLNK(file_stat->st_mode)) permissions[0] = 'l';

    permissions[1] = (file_stat->st_mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (file_stat->st_mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (file_stat->st_mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (file_stat->st_mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (file_stat->st_mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (file_stat->st_mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (file_stat->st_mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (file_stat->st_mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (file_stat->st_mode & S_IXOTH) ? 'x' : '-';

    struct passwd *pw = getpwuid(file_stat->st_uid);
    struct group *gr = getgrgid(file_stat->st_gid);

    char time_str[20];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat->st_mtime));

    printf("%s %lu %s %s %5ld %s %s\n", permissions, 
            file_stat->st_nlink,pw->pw_name, gr->gr_name,
            file_stat->st_size, time_str, file_name);
}


void process_entry(const char *path, const char *name, int show_all, int long_format, int recursive) {
    struct stat file_stat;
    char full_path[4096];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, name);

    if (stat(full_path, &file_stat) == -1) {
        perror("stat error: ");
        return;
    }

    if (long_format) print_file_info(&file_stat, name);
    else printf("%s\n", name);

    if (recursive && S_ISDIR(file_stat.st_mode) && strcmp(name, ".") != 0 && strcmp(name, "..") != 0)
        list_directory(full_path, show_all, long_format, recursive);
}

void list_directory(const char *dir_name, int show_all, int long_format, int recursive) {
    DIR *dir = opendir(dir_name);
    if (!dir) {
        perror("ls: cannot open directory");
        return;
    }

    printf("%s:\n", dir_name);
    struct dirent *entry;
    struct dirent *dir_entries[4096];
    int dir_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (!show_all && entry->d_name[0] == '.') continue;
        if (entry->d_type != DT_DIR) process_entry(dir_name, entry->d_name, show_all, long_format, recursive);
        else dir_entries[dir_count++] = entry;
    }

    for (int i = 0; i < dir_count; i++) process_entry(dir_name, dir_entries[i]->d_name, show_all, long_format, recursive);
    closedir(dir);
}