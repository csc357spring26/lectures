void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* NOTE: Arguments are pass-by-value, and the value of an array is the address
 *       of its first element, which "decays" into a pointer when passed into a
 *       function. Note that the length must be passed separately. Since both
 *       arrays and pointers are addresses; the compiler lets us use array
 *       syntax on pointers. */
void reverse(int arr[], int len) {
    int i;

    for (i = 0; i < len / 2; i++) {
        swap(&arr[i], &arr[len - 1 - i]);
        /* swap(arr + i, arr + (len - 1 - i)); */
    }
}
