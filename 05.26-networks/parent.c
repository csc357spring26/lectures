#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int ptoc[2], ctop[2];

    /* NOTE: In theory, we could just make one pipe and be very careful about
     *       who reads and who writes and when. In practice, we typically just
     *       make one pipe per direction in which data needs to flow. */
    pipe(ptoc);
    pipe(ctop);

    if (!fork()) {
        /* NOTE: By replacing stdin/stdout with the ends of pipes, we can
         *       "trick" the child into using those pipes, despite the fact
         *       that it's about to "exec" code that doesn't know they exist. */
        dup2(ptoc[0], STDIN_FILENO);
        dup2(ctop[1], STDOUT_FILENO);

        /* NOTE: Now that stdin/stdout are used to access the relevant ends of
         *       the pipes, we don't need access to any of the actual pipe
         *       file descriptors within the child. */
        close(ptoc[0]);
        close(ptoc[1]);
        close(ctop[0]);
        close(ctop[1]);

        execlp("./child", "./child", NULL);
        perror("exec");
        exit(EXIT_FAILURE);
    }
    else {
        char buf[81];
        int n;

        close(ptoc[0]);
        close(ctop[1]);

        /* NOTE: First, we need to write to the child, because the child won't
         *       do anything until it receives data from the parent -- if we
         *       try to read first, both parent and child will be "deadlocked",
         *       indefinitely waiting for the other... */
        write(ptoc[1], "parent\n", 7);
        close(ptoc[1]);

        /* NOTE: ...then, we need to read from the child, because there is a
         *       chance that the child's data doesn't all fit in the pipe at
         *       once, in which case we need to make space for more data before
         *       the child can terminate... */
        n = read(ctop[0], buf, 80);
        close(ctop[0]);

        buf[n] = '\0';
        printf("Read \"%s\" from the child-to-parent pipe.\n", buf);

        /* NOTE: ...finally, we can wait for the child to terminate. */
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
