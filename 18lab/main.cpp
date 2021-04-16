#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define MAX_TIME_LENGTH 200
const char* default_args[] = { ".", NULL };

void print_option_list(const char* name, struct stat* fs)
{
    char mode[11];
    char last_changed[FILENAME_MAX] = { 0 };
    struct passwd* owner = getpwuid(fs->st_uid);
    struct group* owner_group = getgrgid(fs->st_gid);

    if (S_IFREG == (fs->st_mode & S_IFMT))
        mode[0] = '-';
    else if (S_IFDIR == (fs->st_mode & S_IFMT))
        mode[0] = 'd';
    else
        mode[0] = '?';

    // user
    mode[1] = (fs->st_mode & S_IRUSR) ? 'r' : '-';
    mode[2] = (fs->st_mode & S_IWUSR) ? 'w' : '-';
    mode[3] = (fs->st_mode & S_IXUSR) ? 'x' : '-';

    // group
    mode[4] = (fs->st_mode & S_IRGRP) ? 'r' : '-';
    mode[5] = (fs->st_mode & S_IWGRP) ? 'w' : '-';
    mode[6] = (fs->st_mode & S_IXGRP) ? 'x' : '-';

    // others
    mode[7] = (fs->st_mode & S_IROTH) ? 'r' : '-';
    mode[8] = (fs->st_mode & S_IWOTH) ? 'w' : '-';
    mode[9] = (fs->st_mode & S_IXOTH) ? 'x' : '-';

    mode[10] = 0;
    printf("%s", mode);
    printf("\t%d", fs->st_nlink);

    if (owner == NULL)
        printf("\t%d", fs->st_uid);
    else
        printf("\t%s", owner->pw_name);

    if (owner_group == NULL)
        printf("\t%d", fs->st_gid);
    else
        printf("\t%s", owner_group->gr_name);

    strftime(last_changed, FILENAME_MAX, "%H:%M %e %b %Y", localtime(&(fs->st_ctime)));
    printf("\t%lu\t%s\t%s\n", fs->st_size, last_changed, name);
}
int main(int argc, char** argv)
{

    struct stat stat;
    const char** dirs;

    if (argc < 2) {
        dirs = default_args;
    } else {
        dirs = (const char**)argv + 1;
    }

    for (int i = 0; dirs[i] != NULL; i++) {
        if (lstat(dirs[i], &stat) == 0) {
            print_option_list(dirs[i], &stat);
        } else {
            perror(dirs[i]);
        }
    }
    return 0;
}
