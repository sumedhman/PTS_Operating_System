// Piping data between processes
// Opens a text file, reads line by line and writes words to stdout using a pipe. Example of piping data.

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{

    char* filename = "sample_words.txt";

    // Open the file.
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    // Create a pipe.
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    close(fd[0]);    // close the read end

    // Read words from the file and write them to the pipe.
    char word[1024];
    while (fscanf(fp, "%s", word) == 1) {
        // write(fd[1], word, strlen(word) + 1);
        write(STDOUT_FILENO, word, strlen(word) + 1);
        write(STDOUT_FILENO, "\n", 2);
    }

    // Close the file and the write end of the pipe.
    fclose(fp);
    close(fd[1]);

    return 0;
}

/*
toor@LAPTOP-RLTA9ELC:~/system_progs$ gcc 7-pipe_word_read.c
toor@LAPTOP-RLTA9ELC:~/system_progs$ ./a.out
Hello
world
This
is
a
sample
input
file
It
can
be
used
to
test
programs
or
to
demonstrate
how
to
read
from
a
file
toor@LAPTOP-RLTA9ELC:~/system_progs$
*/
