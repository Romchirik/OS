#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int main()
{
    struct termios tty, tty_backup;

    int fd;
    if (fd = open("/dev/tty", O_RDONLY) == -1) {
        perror("Opening file error! ");
        return 0;
    }

    if (isatty(fileno(stdin)) == 0) {
        fprintf(stderr, "Stdin is not a terminal\n");
        return 0;
    }

    if (tcgetattr(fd, &tty) == -1) {
        perror("Terminal attributes getting error!");
        return 0;
    }

    tty_backup = tty;
    tty.c_lflag &= ~(ICANON | ISIG | ECHO);
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;
    if (tcsetattr(fd, TCSAFLUSH, &tty) == -1) {
        perror("Terminal attributes setting error!");
        return 0;
    }
    setbuf(stdout, (char*)NULL);
    // setbuf(stdin, (char*) NULL);
    printf("Press any botton...");

    char botton;
    if (read(fd, &botton, 1) == -1) {
        perror("Reading error!");
    }
    printf("\nYou've pressed the botton %c\n", botton);
    if (tcsetattr(fd, TCSAFLUSH, &tty_backup) == -1) {
        perror("Terminal attributes setting error!");
        return 0;
    }
    return 0;
}