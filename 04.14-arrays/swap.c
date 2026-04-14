void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* NOTE: Arguments are pass-by-value, and the value of an array is the address
 *       of its zeroth element, which "decays" into a pointer. Note that the
 *       length must be passed separately if needed. */
void reverse(int arr[], int len) {
    int i;

    for (i = 0; i < len / 2; i++) {
        swap(&arr[i], &arr[len - 1 - i]);

        /* NOTE: Since arrays and pointers are both addresses; the compiler
         *       lets us use array syntax on what is really a pointer. The
         *       above is equivalent to:
         * swap(arr + i, arr + (len - 1 - i)); */
    }
}
