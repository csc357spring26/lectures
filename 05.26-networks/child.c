#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[16];

    /* NOTE: This process, which we would like to execute as a child process
     *       with whom we can communicate via pipes, expects to use stdin and
     *       stdout -- it is entirely unaware of any pipes that its parent
     *       process may have created. */

    fgets(buf, 16, stdin);
    buf[strlen(buf) - 1] = '\0';
    printf("Hello, %s!\n", buf);

    return EXIT_SUCCESS;
}
