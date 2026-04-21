#include <stdlib.h>
#include "list.h"

/* lstcreate: Creates an empty linked list. */
List *lstcreate(void) {
    List *lst = (List *)malloc(sizeof(List));

    /* NOTE: The value of a structure is the whole structure, so, for efficiency,
     *       we typically pass around pointers to structures instead. This means
     *       the structure will have to be dynamically allocated, so as to
     *       avoid returning the address of a local variable. */
    (*lst).head = NULL;

    /* NOTE: This also means that we have to dereference the pointer before we
     *       can access its members. Note that the "." ordinarily has precedence
     *       over the "*". Alternatively, the "->" operator will dereference
     *       the pointer before accessing the member. */
    lst->size = 0;

    return lst;
}

/* lstdestroy: Destroys an existing linked list. */
void lstdestroy(List *lst) {
    Node *node = lst->head;
    
    /* NOTE: Once we free memory, its contents are effectively random -- they
     *       can be reused for future allocations. We might get lucky, and the
     *       data we need might still happen to be there, but in general we
     *       cannot access members after freeing their struct. */

    while (node != NULL) {
        Node *tmp = node->next;
        free(node);
        node = tmp;
    }

    /* NOTE: The compiler does not know what a "linked list" is; it has no way
     *       of knowing what a List's memory represents, that a List is the
     *       only way to access its Nodes, or that being done with a List
     *       implies being done with its Nodes. */

    free(lst);
}

/* lstget: Gets an element in a linked list. */
void *lstget(List *lst, int idx) {
    return NULL;
}

/* lstset: Sets an element in a linked list. */
int lstset(List *lst, int idx, void *val) {
    return 0;
}

/* lstadd: Adds an element to a linked list. */
int lstadd(List *lst, int idx, void *val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;

    if (idx == 0) {
        node->next = lst->head;
        lst->head = node;
    }
    else {
        Node *tmp = lst->head;
        int i;

        for (i = 0; i < idx - 1; i++) {
            tmp = tmp->next;
        }

        node->next = tmp->next;
        tmp->next = node;
    }

    lst->size++;

    /* NOTE: Since we emulated pass-by-reference behavior by taking as argument
     *       a pointer to a list, any modifications to the list are already
     *       visible outside; this return value is an error code to indicate,
     *       for example, whether or not the index was in-bounds. */
    return 0;
}

/* lstremove: Removes an element from a linked list. */
void *lstremove(List *lst, int idx) {
    return NULL;
}
