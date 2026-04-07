/* NOTE: A header file contains information to be shared with other files.
 *       Including a header instructs the compiler to copy the text within that
 *       file into the current source file. */
#include <stdio.h>
#include "add.h"

/* NOTE: A macro is rule for replacing one snippet of code with another. Here,
 *       the compiler is instructed to replace any occurrences of "ONE" with
 *       "1", and "TWO" with "2", from this point in the source code. */
#define ONE 1
#define TWO 2

#define ADD(X, Y) ((X) + (Y))

int main(void) {
    printf("1 + 2: %d\n", 1 + 2);
    printf("add(ONE, TWO): %d\n", add(ONE, TWO));
    printf("ADD(ONE, TWO): %d\n", ADD(ONE, TWO));
    printf("ADD(1, 2) * 3: %d\n", ADD(1, 2) * 3);
    /* printf("ADD(1-, 2): %d\n", ADD(1-, 2)); */

    return 0;
}
