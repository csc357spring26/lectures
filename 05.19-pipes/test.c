#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "spork.h"

int main(void) {
    int status, fds[2];
    pid_t child;

    /* NOTE: Create a pipe to send data from the parent to the child. By doing
     *       this before creating the child process, the child will inherit
     *       access to the pipe by virtue of being a duplicate of the parent. */
    pipe(fds);

    if ((child = spork(5)) == 0) {
        int n;
        char buf[17];

        printf("%ld is the child of %ld.\n", (long)getpid(), (long)getppid());

        close(fds[1]);

        while ((n = read(fds[0], buf, 16)) > 0) {
            buf[n] = '\0';
            printf("%ld read \"%s\" from the pipe.\n", (long)getpid(), buf);
        }

        close(fds[0]);
    }
    else if (child > 0) {
        printf("%ld is the parent of %ld.\n", (long)getpid(), (long)child);

        close(fds[0]);

        write(fds[1], "YOU HAVE FIVE SECONDS TO GO TO YOUR ROOM!", 41);

        /* NOTE: Reading from and writing to pipes are blocking calls; they
         *       will wait for data to be available. By closing the parent's
         *       write end, we notify the child that there will be no more
         *       data coming in the future. */
        close(fds[1]);

        child = wait(&status);
        if (WIFEXITED(status)) {
            printf("%ld exited status %d.\n", (long)child, WEXITSTATUS(status));
        }
        else {
            printf("%ld exited abnormally.\n", (long)child);
        }
    }
    else {
        perror("spork");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
