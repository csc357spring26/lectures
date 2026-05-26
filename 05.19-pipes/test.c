#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "spork.h"

int main(void) {
    int status, fds[2];
    pid_t child;

    /* NOTE: Create a pipe to transfer data from parent to child -- this must
     *       be done before creating the child, so that the child will inherit
     *       access to the pipe by virtue of being a duplicate of the parent. */
    pipe(fds);

    if ((child = spork(5)) == 0) {
        int n;
        char buf[17];

        printf("%ld is the child of %ld.\n", (long)getpid(), (long)getppid());

        close(fds[1]);

        /* NOTE: Read from the "read end" of the pipe, essentially dequeueing
         *       data in the same order it was originally written. */
        while ((n = read(fds[0], buf, 16)) > 0) {
            buf[n] = '\0';
            printf("Read \"%s\" from the pipe.\n", buf);
        }

        close(fds[0]);
    }
    else if (child > 0) {
        printf("%ld is the parent of %ld.\n", (long)getpid(), (long)child);

        close(fds[0]);

        /* NOTE: Write to the "write end" of the pipe, essentially enqueueing
         *       data into the pipe. */
        write(fds[1], "YOU HAVE FIVE SECONDS TO GO TO YOUR ROOM!", 41);

        /* NOTE: Reading from and writing to pipes are blocking calls: reading
         *       from an empty pipe, for example, will wait for data to become
         *       available. By closing the write end, we notify the child that
         *       no more data is actually coming in the future. */
        close(fds[1]);

        child = wait(&status);

        if (WIFEXITED(status)) {
            printf("%ld exited status %d.\n", (long)child, WEXITSTATUS(status));
        }
        else {
            printf("%ld exited abnormally.\n", (long)child);
        }
    }

    return EXIT_SUCCESS;
}
