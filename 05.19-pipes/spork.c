#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

/* NOTE: For simplicity, we'll assume that we only ever "spork" one child at
 *       a time. */
pid_t child;

/* NOTE: Since a handler cannot take any additional arguments (or, for that
 *       matter, return a value), often we need to communicate data to and
 *       from handlers via global variables. */
void handler(int signum) {
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
        /* NOTE: Install a handler to respond to SIGARLM; this must be done
         *       before calling "setitimer", else there is a chance the timer
         *       could go off before we are prepared to respond. */
        action.sa_handler = handler;
        action.sa_flags = SA_RESTART;
        sigemptyset(&action.sa_mask);
        sigaction(SIGALRM, &action, NULL);

        /* NOTE: Create a timer to send a SIGALRM after "timeout" seconds have
         *       elapsed. */
        timer.it_value.tv_sec = timeout;
        timer.it_value.tv_usec = 0;

        /* NOTE: If we wanted to create a recurring timer, we could set a
         *       non-zero interval which would be used to reset the value. */
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 0;

        setitimer(ITIMER_REAL, &timer, NULL);
    }

    return child;
}
