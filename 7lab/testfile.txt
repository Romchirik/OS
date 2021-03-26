#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define _FILE_OFFSET_BITS 64
#define LINE_BUF_SIZE 32

int main(int argc, char** argv)
{
    if (argc < 2) {
        perror("No text file given, please restart with one\n");
        return 0;
    }

    int file_desc = 0;

    if ((file_desc = open(argv[1], O_RDONLY)) == -1) {
        perror("File cannot be open, try again\n");
        return 0;
    }

    int lines_count = 0;
    off_t lines_shifts[BUFSIZ];
    int lines_lengths[BUFSIZ];
    char c_char = 0;
    int cur_line_length = 0;

    struct stat filestat;
    if (fstat(file_desc, &filestat) == -1) {
        perror("Unable to get file size\n");
        return 0;
    }
    off_t file_len = filestat.st_size;

    char* mapped_file = (char*)mmap(NULL, file_len, PROT_READ, MAP_SHARED, file_desc, 0);
    if (*mapped_file == -1) {
        perror("mapping error\n");
        return 0;
    }
    for (int i = 0; i < file_len; i++) {
        if (mapped_file[i] == '\n') {
            lines_lengths[lines_count] = ++cur_line_length;
            lines_shifts[++lines_count] = i;
            cur_line_length = 0;
        } else {
            cur_line_length++;
        }
    }

    //printing the right line
    char line_buffer[LINE_BUF_SIZE];
    if (line_buffer == NULL) {
        return 0;
    }

    int line_buffer_size = LINE_BUF_SIZE;
    int line_number = 0;
    int scanf_return = 0;

    //initializig select
    fd_set file_desc_set;
    struct timeval wait_val;
    int select_retval;

    wait_val.tv_sec = 5;
    wait_val.tv_usec = 0;

    FD_ZERO(&file_desc_set);
    FD_SET(STDIN_FILENO, &file_desc_set);

    while (1) {

        printf("Enter the line you want to print (you have 5 seconds): ");
        fflush(stdout);
        select_retval = select(1, &file_desc_set, NULL, NULL, &wait_val);
        if (select_retval == -1) {
            perror("select error occured\n");
        } else {
            if (select_retval != 0) {

                //resetting timer
                wait_val.tv_sec = 5;
                wait_val.tv_usec = 0;

                if (scanf_return = scanf("%d", &line_number) != 1) {
                    while (fgetc(stdin) != '\n')
                        continue;
                    printf("Input error! Please enter only digits!\n");
                    continue;
                }
                if (line_number == 0) {
                    close(file_desc);
                    return 0;
                }
                if (line_number > lines_count || line_number < 0) {
                    printf("Wrong line number!\n");
                    continue;
                }
                line_number--;

                write(STDOUT_FILENO, mapped_file + lines_shifts[line_number] + 1, lines_lengths[line_number] + 1);
            } else {
                return 0;
            }
        }
    }

    close(file_desc);
    return 0;
}