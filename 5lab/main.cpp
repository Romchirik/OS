#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
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

    //making matrixes of lengths and shifts
    while (read(file_desc, &c_char, 1)) {
        if (c_char == '\n') {
            lines_lengths[lines_count] = ++cur_line_length;
            lines_shifts[++lines_count] = lseek(file_desc, 0, SEEK_CUR);
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
    // use select for input
    while (1) {
        if (scanf_return = scanf("%d", &line_number) != 1) {
            while (fgetc(stdin) != '\n')
                continue;
            perror("Input error! Please enter only digits!\n");
            continue;
        }

        if (line_number == 0) {
            break;
        }
        if (line_number > lines_count || line_number < 0) {
            perror("Wrong line number!\n");
            continue;
        }
        line_number--;
        lseek(file_desc, lines_shifts[line_number], SEEK_SET);

        for (int i = 0; i < lines_lengths[line_number] / LINE_BUF_SIZE; i++) {
            read(file_desc, line_buffer, LINE_BUF_SIZE);
            write(STDOUT_FILENO, line_buffer, LINE_BUF_SIZE);
        }
        read(file_desc, line_buffer, lines_lengths[line_number] % LINE_BUF_SIZE);
        write(STDOUT_FILENO, line_buffer, lines_lengths[line_number] % LINE_BUF_SIZE);
    }

    close(file_desc);
    return 0;
}
