#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/* NOTE: Since there is no exception mechanism in C, when a system call fails,
 *       it will set the global variable "errno" to indicate the cause of the
 *       failure -- this variable contains the reason for the last failure. */
extern int errno;

int main(int argc, char *argv[]) {
    struct stat buf;

    if (argc < 2) {
        /* NOTE: In UNIX, all I/O appears to be file I/O. Every process starts
         *       with 3 open "files": stdin for terminal input, stdout for
         *       terminal output, and stderr for error messages. */
        fprintf(stderr, "Too few arguments\n");
        return EXIT_FAILURE;
    }

    if (stat(argv[1], &buf) < 0) {
        /* NOTE: The values of "errno" are not standardized, but the standard
         *       library function "perror" can be used to look up an error
         *       number and print an appropriate message. */
        fprintf(stderr, "Error %d\n", errno);
        perror(argv[1]);
        return EXIT_FAILURE;
    }
    else {
        /* NOTE: Each file is implemented as exactly one inode, which contains
         *       a variety of metadata but *not* a filename. Files don't have
         *       names; they are identified by device/inode numbers. */
        printf("device: %ld\n", (long)(buf.st_dev));
        printf("inode:  %ld\n", (long)(buf.st_ino));
        printf("size:   %ld\n", (long)(buf.st_size));
        printf("blocks: %ld\n", (long)(buf.st_blocks));
    }

    return EXIT_SUCCESS;
}
