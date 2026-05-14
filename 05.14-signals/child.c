#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/* NOTE: A handler is a function that responds to signals. Since we cannot
 *       predict when a signal will occur, we cannot predict when we need to
 *       call the function; the OS will call it for us. Effectively, a handler
 *       has no caller, so it cannot take more arguments or return anything. */
void handler(int signum) {
    /* NOTE: This is technically unsafe; "printf" is not async-signal-safe. We
     *       get away with it because there are no other calls to "printf" that
     *       could be running at this time, but if there were, this would
     *       likely corrupt their internal string buffers. */
    if (signum == SIGINT) {
        printf("But CONNOR lets their processes stay up on the CPU as long as they want!\n");
    }
    else if (signum == SIGQUIT) {
        printf("But SAGE lets their processes eat as much memory as they want before dinner!\n");
    }
    else {
        printf("Handling signal %d.\n", signum);
    }
}

int main(void) {
    struct sigaction action;

    printf("%ld is a child of %ld.\n", (long)getpid(), (long)getppid());

    action.sa_handler = handler;
    action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);

    /* NOTE: This changes the default action associated with SIGINT (Ctrl+c) to
     *       call "handler" instead. If we cared to save and later restore the
     *       existing action, we could pass a pointer to another structure
     *       instead of NULL, to be populated with existing settings. */
    sigaction(SIGINT, &action, NULL);

    /* NOTE: Likewise, this uses "handler" to effectively ignore SIGQUIT
     *       (Ctrl+\). This might legitimately be useful to ensure that a
     *       program shuts down gracefully, however, SIGSTOP (Ctrl+z) and
     *       SIGKILL cannot be handled, blocked, or otherwise ignored. */
    sigaction(SIGQUIT, &action, NULL);
    sigaction(SIGSTOP, &action, NULL);
    sigaction(SIGKILL, &action, NULL);

    while (1);

    return EXIT_SUCCESS;
}
