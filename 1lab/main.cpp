#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <ulimit.h>
#include <unistd.h>

extern char** environ;

int main(int argc, char** argv) {
    int current_argument;
    char options[] = "ispuU:cC:dvV:";
    struct rlimit rlp;
    char** currentEnvVar;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s options\n", argv[0]);
        exit(0);
    }

    while ((current_argument = getopt(argc, argv, options)) != EOF) {
        switch (current_argument) {
            case 'i':
                printf("user real id: %ld\n", getuid());
                printf("user effective id: %ld\n", geteuid());
                printf("group real id: %ld\n", getgid());
                printf("group effective id: %ld\n", getegid());
                break;
            case 's':
                setpgid(0, 0);
                break;
            case 'p':
                printf("process id: %ld\n", getpid());
                printf("parent process id: %ld\n", getppid());
                printf("group process id: %ld\n", getpgid(0));
                break;
            case 'U':
                if (ulimit(UL_SETFSIZE, atol(optarg)) == -1) {
                    perror("Must be super-user to increase ulimit\n");
                }
                break;
            case 'u':
                printf("ulimit = %ld\n", ulimit(UL_GETFSIZE, 0));
                break;
            case 'c':
                getrlimit(RLIMIT_CORE, &rlp);
                printf("core size = %ld\n", rlp.rlim_cur);
                break;
            case 'C':
                getrlimit(RLIMIT_CORE, &rlp);
                rlp.rlim_cur = atol(optarg);
                if (setrlimit(RLIMIT_CORE, &rlp) == -1)
                    perror("Must be super-user to increase core\n");
                break;
            case 'd':
                printf("current working directory is: %s\n", getcwd(NULL, 100));
                break;
            case 'v':
                printf("environment variables are:\n");
                for (currentEnvVar = environ; *currentEnvVar; currentEnvVar++)
                    printf("%s\n", *currentEnvVar);
                break;
            case 'V':
                putenv(optarg);
                break;
        }
    }
    return 0;
}

