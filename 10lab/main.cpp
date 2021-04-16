#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("No arguments given, Terminating...\n");
    }

    pid_t pid, return_value;
    int status;
    siginfo_t info;
    if ((pid = fork()) < 0) {
        perror("Unable to create child process. Terminating...\n");
    } else if (pid == 0) {
        execvp(argv[1], &argv[1]);
        perror(argv[1]);
        exit(17);
    } else if (pid > 0) {

        return_value = wait(&status);
        if (return_value == -1) {
            perror("Wait ended with en error!\n");
        }
        if (WIFEXITED(status)) {
            printf("Child exited with code %i\n", WEXITSTATUS(status));
        }
    }
    return 0;
}
