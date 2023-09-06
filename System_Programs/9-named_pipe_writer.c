// Named pipes (FIFO)
// Writer process opens FIFO pipe for writing data read by reader process.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char *message = "Hello, named pipe!";
    ssize_t bytes_written;

    fd = open("myfifo", O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    bytes_written = write(fd, message, strlen(message));
    if (bytes_written == -1) {
        perror("write");
        return 1;
    }

    close(fd);
    return 0;
}
