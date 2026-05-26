#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int ptoc[2], ctop[2], n;
    char buf[81];

    /* NOTE: In theory, if we were very careful about who read and who wrote
     *       and when, everyone could share one pipe. In practice, we typically
     *       just make one pipe for each direction in which data needs to
     *       flow: in this case, one parent-to-child and one child-to-parent. */
    pipe(ptoc);
    pipe(ctop);

    if (!fork()) {
        /* NOTE: By replacing stdin and stdout with the ends of pipes, we can
         *       essentially "trick" a child executable into using pipes even
         *       though it has no idea that those pipes exist. */
        dup2(ptoc[0], STDIN_FILENO);
        dup2(ctop[1], STDOUT_FILENO);

        close(ptoc[0]);
        close(ptoc[1]);
        close(ctop[0]);
        close(ctop[1]);

        execlp("./child", "./child", NULL);
        perror("exec");
        exit(EXIT_FAILURE);
    }
    else {
        close(ptoc[0]);
        close(ctop[1]);

        /* NOTE: First, the parent must write data for the child to consume. If
         *       both the parent and the child try to read first, they will be
         *       "deadlocked" indefinitely waiting for the other to write. */
        write(ptoc[1], "parent\n", 7);
        close(ptoc[1]);

        /* NOTE: Then, the parent must read the data the child is producing. If
         *       the child's data is too large to fit in the pipe at once, the
         *       parent has to start reading to make space before the child can
         *       finish. */
        n = read(ctop[0], buf, 80);
        close(ctop[0]);

        buf[n] = '\0';
        printf("Read \"%s\" from the child-to-parent pipe.\n", buf);

        /* NOTE: Finally, the parent must wait for its child.*/
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
