#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

int main(int argc, char *argv[]) {
    struct stat buf;

    if (argc < 2) {
        /* NOTE: In UNIX, all I/O appears to be file I/O. Every process begins
         *       with three open "files": stdin for terminal input, stdout for
         *       terminal output, and stderr for error messages. To display an
         *       error message is to write to the "file" stderr. */
        fprintf(stderr, "Too few arguments.\n");
        return EXIT_FAILURE;
    }

    if (stat(argv[1], &buf) < 0) {
        /* NOTE: In case of failure, system calls will set the global variable
         *       "errno" to indicate the reason for the failure. These numbers
         *       are not standardized, but the standard library function
         *       "perror" can be used to print a human-readable message. */
        fprintf(stderr, "%s: %d\n", argv[1], errno);
        perror(argv[1]);
        return EXIT_FAILURE;
    }
    else {
        /* NOTE: Files are implemented as inodes and stored in blocks, but they
         *       do not have names: each file is uniquely identified by its
         *       device/inode number pair; the parent directory maps filenames
         *       to inodes for human readability. */
        printf("device: %ld\n", (long)(buf.st_dev));
        printf("inode:  %ld\n", (long)(buf.st_ino));
        printf("size:   %ld\n", (long)(buf.st_size));
        printf("blocks: %ld\n", (long)(buf.st_blocks));
    }

    return EXIT_SUCCESS;
}
