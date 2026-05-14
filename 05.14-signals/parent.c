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
        /* NOTE: By replacing the child process with the contents of another
         *       executable, the child is no longer limited to executing only
         *       the code that it inherited from its parent. By convention, the
         *       first argument should always be the name of the executable. */
        execlp("./child", "child", NULL);

        /* NOTE: Assuming "exec" succeeds, the current process is replaced with
         *       the contents of another executable, which means any code below
         *       "exec" ceases to exist. Effectively, "exec" is called once
         *       and, if it succeeds, it *never returns at all*. */
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
