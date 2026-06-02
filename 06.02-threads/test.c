#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 1024

/* NOTE: Since the pthreads library has to work with any arbitrary function,
 *       the function will have to take a void pointer and return a void
 *       pointer. Those pointers can point to anything; we'll create a struct
 *       to encapsulate the data we actually want to pass. */
typedef struct Arg {
    int *arr, n, x;
} Arg;

/* NOTE: If two threads "race" to increment the same counter, there is a chance
 *       that it only gets incremented once. We need to protect the counter
 *       with a "mutex lock", a resource that only one thread can acquire at
 *       once and which no thread can be interrupted while acquiring. */
static pthread_mutex_t lock;

/* NOTE: Like processes, threads execute concurrently with their own registers
 *       and runtime stacks. Unlike processes, threads share resources such as
 *       the data segment. By putting the "count" in global memory, all of the
 *       threads can increment it without any interprocess communication. */
static int count = 0;

/* NOTE: This function will eventually be passed to "pthread_create"; it will
 *       essentially be the "main" function of a new thread. Once it returns,
 *       that new thread will terminate and it can be joined with the main
 *       thread. */
void *search(void *ptr) {
    Arg *arg = (Arg *)ptr;
    int i;

    for (i = 0; i < arg->n; i++) {
        if (arg->arr[i] == arg->x) {
            /* NOTE: This is the "critical section", the code that only one
             *       thread should execute at once. No two threads can have the
             *       lock, so no two threads can get past "pthread_mutex_lock"
             *       and into the critical section at the same time. */
            pthread_mutex_lock(&lock);

            /* NOTE: Only "lock" itself is mutually exclusive; "count" is
             *       otherwise unprotected, and threads have to cooperatively
             *       agree to acquire the lock before attempting to increment
             *       the counter. */
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

    /* NOTE: Counting occurrences of a value cannot be meaningfully broken down
     *       into parallelizable subtasks, so this problem calls for data
     *       parallelism: we'll split the dataset (the array) in half, and
     *       create separate threads to search each half. */
    args[0].arr = arr;
    args[0].n = n;
    args[0].x = x;
    args[1].arr = arr + SIZE / 2;
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
