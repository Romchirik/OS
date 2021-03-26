#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main (int argc, char **argv) {

    printf("\nbefore using setuid()\n");
    printf("\treal user ID: %d\n", getuid());
    printf("\teffective user id: %d\n", geteuid());

    FILE* file = fopen(argv[1], "r");

    if (file == NULL){
        perror("couldn't open file");
    } else {
        printf("file was opened sucessfully\n");
    }
    fclose(file);

    setuid(getuid());
    printf("after using setuid()\n");

    printf("\treal user ID %d\n", getuid());
    printf("\teffective user id: %d\n", geteuid());

    file = fopen(argv[1], "r");
    if (file == NULL){
        perror("couldn't open file\n");
    } else {
        printf("file was opened successfully\n");
    }
    fclose(file);

    return 0;
}
