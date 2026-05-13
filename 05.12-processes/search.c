#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINELEN 81

int fsearch(char *, char *);

int main(int argc, char *argv[]) {
    int i, status = EXIT_FAILURE;
    pid_t child;

    /* NOTE: "fork" duplicates the now-parent process -- the child process will
     *       have the same contents in memory as the parent, which means the
     *       child will be doing exactly the same thing as the parent, which
     *       means "fork" must return *twice*, both to parent and to child. */
    for (i = 2; i < argc; i++) {
        if ((child = fork()) == 0) {
            printf("%ld is the child of %ld.\n", (long)getpid(), (long)getppid());
            return fsearch(argv[i], argv[1]);
        }
        else {
            printf("%ld is the parent of %ld.\n", (long)getpid(), (long)child);
        }
    }

    /* NOTE: It is the parent's responsibility to wait for each and every one
     *       of its children, so as to clean up any resources associated with
     *       the resulting zombies, however, we need to make sure we create all
     *       of the children before we start waiting. */
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
