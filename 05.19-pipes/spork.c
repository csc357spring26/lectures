#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

/* NOTE: For simplicity, we'll assume we only spork one child at a time, else
 *       this would need to be some sort of dynamically allocated collection of
 *       multiple child PIDs. */
static pid_t child;

/* NOTE: Since a handler effectively has no caller, it cannot take any more
 *       arguments or return a value. Instead, to communicate data to and from
 *       a handler, we can leave it in global variables. If this makes us
 *       uncomfortable, we can declare those variables as "static", so that
 *       they are not accessible outside of this file. */
void handler(int signum) {
    (void)signum;

    kill(child, SIGKILL);
}

/* spork: Creates a new resource-limited process. */
pid_t spork(time_t timeout) {
    struct rlimit limit;
    struct sigaction action;
    struct itimerval timer;

    if ((child = fork()) == 0) {
        /* NOTE: Lower both the soft and hard limits on the number of processes
         *       to 1 within the child process, so that it cannot create any
         *       child processes of its own. */
        getrlimit(RLIMIT_NPROC, &limit);
        limit.rlim_cur = 1;
        limit.rlim_max = 1;
        setrlimit(RLIMIT_NPROC, &limit);
    }
    else {
        /* NOTE: Install a handler to respond to SIGARLM -- note that this must
         *       be done *before* setting the corresponding timer, else there
         *       is a chance the timer could elapse before the handler is
         *       installed. */
        action.sa_handler = handler;
        action.sa_flags = SA_RESTART;
        sigemptyset(&action.sa_mask);
        sigaction(SIGALRM, &action, NULL);

        /* NOTE: Create a timer to send a SIGARLM after "timeout" seconds have
         *       elapsed in real time. */
        timer.it_value.tv_sec = timeout;
        timer.it_value.tv_usec = 0;

        /* NOTE: In this case, the timer does not need to repeat; if it did,
         *       the "it_interval" determines the value that will be used to
         *       reset the "it_value" every time the timer elapses. */
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 0;
        setitimer(ITIMER_REAL, &timer, NULL);

        /* NOTE: Compared to simply sleeping, setting a timer allows us to do
         *       something else while waiting for the timer to elapse. If we
         *       don't have anything else useful to do, "pause" suspends
         *       execution until a signal is received, so as to avoid the
         *       need for "busy waiting".
         * pause(); */
    }

    return child;
}
