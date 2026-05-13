#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINELEN 81

int fsearch(char *, char *);

int main(int argc, char *argv[]) {
    int status = EXIT_FAILURE, i;
    pid_t child;

    /* NOTE: "fork" duplicates the parent process -- the child will have the
     *       same contents in memory, which means the child will be executing
     *       the same instructions. Effectively, fork is called once in the
     *       parent and it returns *twice* to both parent and child. */
    for (i = 2; i < argc; i++) {
        if ((child = fork()) == 0) {
            printf("%ld is the child of %ld.\n", (long)getpid(), (long)getppid());
            return fsearch(argv[i], argv[1]);
        }
        else {
            printf("%ld is the parent of %ld.\n", (long)getpid(), (long)child);
        }
    }

    /* NOTE: Parents are responsible for waiting for their children, so as to
     *       clean up any resources associated with the resulting zombies. In
     *       this case, however, we need to make sure that all of the children
     *       are created before we start waiting. */
    for (i = 2; i < argc; i++) {
        child = wait(&status);

        if (WIFEXITED(status)) {
            printf("%ld exited with status %d.\n", (long)child, WEXITSTATUS(status));
        }
        else {
            printf("%ld exited abnormally.\n", (long)child);
        }
    }

    return EXIT_SUCCESS;
}

/* fsearch: Prints occurrences of a string in a file. */
int fsearch(char *fname, char *str) {
    int status = EXIT_FAILURE;
    char buf[LINELEN];
    FILE *file = fopen(fname, "r");

    while (fgets(buf, LINELEN, file) != NULL) {
        if (strstr(buf, str) != NULL) {
            printf("%s: %s", fname, buf);
            status = EXIT_SUCCESS;
        }
    }

    fclose(file);
    return status;
}
