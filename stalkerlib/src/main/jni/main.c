#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void printdironly(const char *name) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;
    else {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR) {
                char path[1024];
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                    continue;

                snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
                printdironly(path);
            } else {
                char path[1024];
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                    continue;
                snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);

                struct stat fileStat;
                if (stat(path, &fileStat) < 0)
                    continue;
                else {
                    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
                    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
                    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
                    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
                    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
                    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
                    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
                    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
                    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
                    printf(" %s/%s\n", path, entry->d_name);
                }
            }
        }
        closedir(dir);
    }
}

int main(int argc, char *argv[]) {
    printf("\nlist of files: \n");

    printdironly("/proc");

    printf("\nfinished\n");

    return 0;
}