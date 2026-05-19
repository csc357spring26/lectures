#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "spork.h"

int main(void) {
    int status;
    pid_t child;

    if ((child = spork(5)) == 0) {
        printf("%ld is the child of %ld.\n", (long)getpid(), (long)getppid());

        while (fork() < 0) {
            perror("fork");
            sleep(1);
        }
    }
    else {
        printf("%ld is the parent of %ld.\n", (long)getpid(), (long)child);
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
