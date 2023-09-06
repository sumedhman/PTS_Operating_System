// Named pipes (FIFO)
// Reader process opens FIFO pipe for reading data written by writer process.
// Demonstration code on inter-process communication

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char buffer[1024];
    ssize_t bytes_read;

    fd = open("myfifo", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read");
        return 1;
    }

    printf("Received: %.*s\n", (int)bytes_read, buffer);

    close(fd);
    return 0;
}

// The mkfifo command sets up a FIFO, optionally setting permissions 
// at the same time. This inter-process communication provides a very 
// useful multitasking ability in a really easy-to-use-and-understand manner.

/*
TERMINAL 1:

toor@LAPTOP-RLTA9ELC:~/system_progs$ gcc 8-named_pipe_reader.c -o reader.out
toor@LAPTOP-RLTA9ELC:~/system_progs$ gcc 9-named_pipe_writer.c -o writer.out
toor@LAPTOP-RLTA9ELC:~/system_progs$ ./reader.out
open: No such file or directory
toor@LAPTOP-RLTA9ELC:~/system_progs$ mkfifo myfifo
toor@LAPTOP-RLTA9ELC:~/system_progs$ ./reader.out
Received: Hello, named pipe!
toor@LAPTOP-RLTA9ELC:~/system_progs$

TERMINAL 2:

toor@LAPTOP-RLTA9ELC:~/system_progs$ 	
*/
