#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char** environ;

int execvpe(char* file, char* argv[], char* envp[])
{
    if (file == NULL) {
        perror("Too few arguments to function 'execvpe'");
        return -1;
    }
    char** environ_dump = environ;
    environ = envp;
    execvp(file, argv);
    environ = environ_dump;
    return -1;
}

int main(int argc, char* argv[], char* envp[])
{
    if (argc < 2) {
        printf("Please pass at least one programm name to launch");
        return 0;
    }
    if (envp == NULL) {
        perror("ENVP error: too few env == NULL");
    }

    if (putenv("TZ=America/Los_angeles") < 0) {
        perror("putenv() error");
    }

    execvpe(argv[1], &argv[1], envp);
    perror(argv[1]);
    return 0;
}