#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    if (!fork()) {
        execlp("./child", "./child", NULL);
        perror("exec");
        exit(EXIT_FAILURE);
    }
    else {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
