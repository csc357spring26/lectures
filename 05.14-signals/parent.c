#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int status;
    pid_t child;

    if ((child = fork()) == 0) {
        /* NOTE: Rather than writing both parent and child code in the same
         *       program, "exec" replaces a process with another executable, so
         *       that the child is not limited to what it inherits from its
         *       parent. By convention, the first argument is the name. */
        execlp("./child", "child", NULL);

        /* NOTE: The only way to return from "exec" is if it failed. If it
         *       succeeds, whatever code used to be after "exec" ceases to
         *       exist. Effectively, "exec" is called once and it never
         *       returns at all. */
        perror("execlp");
        return EXIT_FAILURE;
    }
    else {
        printf("%ld is the parent of %ld.\n", (long)getpid(), (long)child);

        sleep(1);
        kill(child, SIGINT);
        sleep(1);
        kill(child, SIGQUIT);
        sleep(1);
        kill(child, SIGSTOP);
        kill(child, SIGKILL);

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
