#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(const int argc, const char* argv[])
{
    if (argc < 2) {
        perror("No text file given, please restart with one\n");
        return 0;
    }

    int child_pid;
    siginfo_t info;

    if ((child_pid = fork()) == -1) {
        perror("Unable to create child process. Terminating...");
        return 0;
    } else if (child_pid == 0) {
        if (execl("/bin/cat", "cat", argv[1], (char*)NULL) < 0) {
            perror("execl error");
            return 0;
        }
    } else if (child_pid > 0) {
        printf("parent waiting for child %d\n", child_pid);
        int wait_retval = waitid(P_PID, child_pid, &info, WEXITED);
        if (wait_retval == -1) {
            perror("waitid error");
            return 0;
        }
        printf("Parent process writing in the end\n");
    }

    return 0;
}