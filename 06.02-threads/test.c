#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 1024

/* NOTE: Since pthreads have to work with any function, the functions they
 *       parallelize must take void pointers and return void pointers. Rather,
 *       we must create a structure to encapsulate the actual arguments, and
 *       we can then pass a pointer to that structure. */
typedef struct Arg {
    int *arr, n, x;
} Arg;

/* NOTE: This creates a scenario where both threads "race" to increment the
 *       same variable. We need to protect that variable with a "mutex lock",
 *       a mutually exclusive resource which at most one thread may possess at
 *       any given time. */
pthread_mutex_t lock;

/* NOTE: Unlike processes, threads share the same text/data segment, the same
 *       heap, and the same resources such as open files. To communicate data
 *       from one thread to another, we can simply leave it in a global
 *       variable that all threads can access. */
static int count = 0;

void *search(void *ptr) {
    Arg *arg = (Arg *)ptr;
    int i;

    for (i = 0; i < arg->n; i++) {
        if (arg->arr[i] == arg->x) {
            /* NOTE: This is the "critical section": the code that at most one
             *       thread should execute at once. No more than one thread may
             *       have the lock, thus no more than one thread can make it
             *       past "pthread_mutex_lock" at the same time. */
            pthread_mutex_lock(&lock);

            /* NOTE: Only "lock" is mutually exclusive; "count" itself is still
             *       unprotected, and the threads that use "count" have to
             *       cooperatively agree to acquire "lock" before they entire
             *       the critical section. */
            count++;

            pthread_mutex_unlock(&lock);
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    int arr[SIZE], i, n, x;
    pthread_t tids[2];
    Arg args[2];

    for (i = 0; i < SIZE; i++) {
        arr[i] = rand() % 10;
    }

    x = strtol(argv[1], NULL, 10);
    n = SIZE / 2;

    /* NOTE: This is data parallelism: we split the dataset (the array to be
     *       searched) in half, and create one thread for each half. The first
     *       thread will search the first half; the second, the second half. */
    args[0].arr = arr;
    args[0].n = n;
    args[0].x = x;
    args[1].arr = arr + n;
    args[1].n = n;
    args[1].x = x;

    pthread_mutex_init(&lock, NULL);
    pthread_create(&tids[0], NULL, search, &args[0]);
    pthread_create(&tids[1], NULL, search, &args[1]);
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    pthread_mutex_destroy(&lock);

    printf("%d\n", count);
    return 0;
}
