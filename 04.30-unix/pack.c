#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char stob(char *);

int main(int argc, char* argv[]) {
    unsigned char byte;
    char buf[8];

    /* NOTE: When a file is opened, an entry is created in a behind-the-scenes
     *       array of open files, the "file table". The system call "open"
     *       returns an integer "file descriptor", an index into the table of
     *       open files. */
    int src, dest, n;

    /* NOTE: Standard library functions like "fopen" encapsulate the most
     *       common functionality. For example, "fopen" will always truncate an
     *       existing file opened for writing. If we don't want those defaults,
     *       then we can make the system call "open" directly ourselves. */
    src = open(argv[1], O_RDONLY);
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    /* NOTE: System calls are exposed as though they were C functions, but they
     *       are more expensive than ordinary function calls: they have to
     *       securely transfer control to and from the OS, which requires far
     *       more work than just jumping to a subroutine... */
    while ((n = read(src, buf, sizeof(char) * 8)) > 0) {
        for (; n < 8; n++) {
            buf[n] = '0';
        }

        byte = stob(buf);
        write(dest, &byte, sizeof(char) * 1);
    }

    /* NOTE: There are a finite number of file descriptors available -- the
     *       file table has fixed size. If we only ever open files without
     *       closing them, eventually the OS will deny requests to open any
     *       more files. */
    close(src);
    close(dest);

    return 0;
}

unsigned char stob(char *bits) {
    unsigned char byte = 0, mask;

    for (mask = 1 << 7; mask > 0; mask >>= 1) {
        if (*(bits++) == '1') {
            byte |= mask;
        }
    }

    return byte;
}
