/* NOTE: In computer science, there is very little penalty to simply trying
 *       something to see if or how it works. We should get into the habit of
 *       testing something any time we learn something new. */

#include <stdio.h>

int main(void) {
    /* NOTE: The function "main" is the entry point. Its arguments are the
     *       command line arguments, which we can declare as "void" if we need
     *       to assure the compiler that we're not going to use them. */

    printf("Hello, world!\n");


    /* NOTE: This return value is an exit status, where by convention returning
     *       0 indicates that no errors occurred. */
    return 0;
}
