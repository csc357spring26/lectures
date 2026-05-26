#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[16];

    fgets(buf, 16, stdin);
    buf[strlen(buf) - 1] = '\0';
    printf("Hello, %s!\n", buf);

    return EXIT_SUCCESS;
}
