#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/* NOTE: A signal handler is a function that will be called in response to a
 *       signal. Since signals are asynchronous, we can't predict when this
 *       function ought to be called; the OS will do it for us -- effectively,
 *       this function *has no caller*. */
void handler(int signum) {
    /* NOTE: This handler is technically unsafe; only async-signal-safe
     *       functions ought to be called in handlers. In this case, "printf"
     *       has to build it string in an internal buffer, so if a signal
     *       occurs during a call to "printf", that buffer can be corrupted. */
    if (signum == SIGINT) {
        printf("But CONNOR lets his children eat CPU time before dinner!\n");
    }
    else if (signum == SIGQUIT) {
        printf("But IROON lets his children stay up as long as they want!\n");
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

    /* NOTE: This installs "handler" in response to SIGINT (Ctrl+C). If we cared
     *       to save a previously existing handler, we could pass as the third
     *       argument a pointer to another struct sigaction, which would be
     *       populated with the previously existing settings. */
    sigaction(SIGINT, &action, NULL);

    /* NOTE: Likewise, this installs "handler" in response to SIGQUIT (Ctrl+\).
     *       However, SIGSTOP (Ctrl+z) and SIGKILL cannot be handled or
     *       otherwise ignored. */
    sigaction(SIGQUIT, &action, NULL);
    sigaction(SIGSTOP, &action, NULL);
    sigaction(SIGKILL, &action, NULL);

    while (1);

    return EXIT_SUCCESS;
}
