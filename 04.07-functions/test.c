/* NOTE: This instructs the compiler to copy the textual contents of "stdio.h"
 *       from the standard library and "add.h" from the current directory into
 *       this source file. */
#include <stdio.h>
#include "add.h"

/* NOTE: This instructs the compiler to replace the text "ONE" with the text
 *       "1", and "TWO" with "2", throughout the rest of this file. Note that
 *       these are not variables, and they do not take space in memory. */
#define ONE 1
#define TWO 2

/* NOTE: Even though this looks like a function, it will be substantially more
 *       efficient; it likely expands into a single machine instruction to add
 *       two registers rather than a full-blown function call. Note that both
 *       the arguments and the overall expression must be parenthesized for
 *       safety. */
#define ADD(X, Y) ((X) + (Y))

int main(void) {
    printf("1 + 2: %d\n", 1 + 2);
    printf("add(1, 2): %d\n", add(ONE, TWO));
    printf("ADD(1, 2): %d\n", ADD(1, 2));
    printf("ADD(1, 2) * 3: %d\n", ADD(1, 2) * 3);
    printf("ADD(1 - 3, 2): %d\n", ADD(1 - 3, 2));

    return 0;
}
