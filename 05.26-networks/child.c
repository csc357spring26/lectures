#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[16];

    /* NOTE: This program is entirely unaware of the existence of any pipes; it
     *       expects to communicate via stdin and stdout. */

    fgets(buf, 16, stdin);
    buf[strlen(buf) - 1] = '\0';
    printf("Hello, %s!\n", buf);

    return EXIT_SUCCESS;
}
