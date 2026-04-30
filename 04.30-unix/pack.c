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
     *       "file table", essentially just a big array of open files. The
     *       system call open returns a "file descriptor", an index into the
     *       file table. */
    int src, dest, n;

    /* NOTE: Standard library functions like fopen encapsulate the most common
     *       functionality. For example, fopen always truncates a file opened
     *       for writing, and always applies the default permissions. If we
     *       don't want these defaults, then we can call open directly. */
    src = open(argv[1], O_RDONLY);
    dest = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    /* NOTE: In UNIX, system calls are exposed as C functions, but a system
     *       call takes longer than an ordinary function call: it must transfer
     *       control to and from the OS. Standard library functions like fread
     *       don't avoid calling read, but they will read in more bytes than we
     *       ask for and store the excess in a behind-the-scenes buffer in
     *       memory, so that they can just give us data from the buffer in
     *       future in order to limit the number of system calls. */
    while ((n = read(src, buf, sizeof(char) * 8)) > 0) {
        for (; n < 8; n++) {
            buf[n] = '0';
        }

        byte = stob(buf);
        write(dest, &byte, sizeof(char) * 1);
    }

    /* NOTE: There are a finite number of file descriptors available -- the
     *       file table has fixed size. If we only ever call open without ever
     *       calling close, eventually, the operating system will deny our
     *       requests to open additional files. */
    close(src);
    close(dest);

    return EXIT_SUCCESS;
}

unsigned char stob(char *bits) {
    unsigned char byte = 0, mask;

    for (mask = 1 << 7; mask > 0; mask >>= 1) {
        if (*(bits++) == '1') {
            byte = byte | mask;
        }
    }

    return byte;
}
