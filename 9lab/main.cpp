#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(const int argc, const char* argv[])
{
    if (argc < 2) {
        perror("No text file given, please restart with one\n");
        return 0;
    }

    int pid;
    printf(argv[1]);
    int ret = execl("cat", argv[1], (char*)NULL);

    if (ret < 0) {
        perror("Some err occured");
    }
    // if ((pid = fork()) == -1) {
    //     perror("Unable to create child process. Terminating...");
    //     return 0;
    // } else if (pid == 0) {
    //     // char command[FILENAME_MAX];
    //     // sprintf(command, "cat %s\n", argv[1]);
    //     // system(command);

    // } else {
    //     printf("Hello from parent!\n");
    //     printf("Hello world!\n");
    //     printf("Do you even code?\n");
    // }

    return 0;
}