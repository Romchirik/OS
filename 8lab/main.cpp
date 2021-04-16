#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    struct flock lock;
    char command[FILENAME_MAX];

    int file_descriptor;

    if ((file_descriptor = open(argv[1], O_RDWR)) == -1) {
        perror("File cannot be open\n");
        return 0;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(file_descriptor, F_SETLK, &lock) == -1) {
        perror("failed to lock file");
        return 1;
    }

    sprintf(command, "vim %s\n", argv[1]);
    system(command);

    lock.l_type = F_UNLCK;

    if (fcntl(file_descriptor, F_SETLK, &lock) == -1) {
        perror("failed to unlock file");
    }

    close(file_descriptor);
    return 0;
}
