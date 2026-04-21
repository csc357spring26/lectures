#include <stdlib.h>
#include "list.h"

/* lstcreate: Creates an empty linked list. */
List *lstcreate(void) {
    List *lst = (List *)malloc(sizeof(List));

    /* NOTE: Since the list needs to persist after this function returns but we
     *       don't know how many lists we will need, it must be dynamically
     *       allocated. We then have a pointer to a structure, which must be
     *       dereferenced before we can access its members. */
    (*lst).head = NULL;

    /* NOTE: Above, the "." has precedence over the "*", so the "*lst" must be
     *       parenthesized. Alternatively, it is equivalent to "->". Note that
     *       the value of a structure is the whole structure, but we can always
     *       opt-in to pass-by-reference behavior by using pointers. */
    lst->size = 0;

    return lst;
}

/* lstdestroy: Destroys an existing linked list. */
void lstdestroy(List *lst) {
    /* NOTE: The List is the only way to access the Nodes -- once we free the
     *       List, we will have no way of accessing the Nodes inside. Before
     *       we lose access, we need to free each and every Node individually.
     *       In general, we can't access a member after freeing its struct. */
    Node *node = lst->head;

    while (node != NULL) {
        Node *tmp = node->next;
        free(node);
        node = tmp;
    }

    /* NOTE: This only frees the List structure; it does not free any of the
     *       Nodes inside. The compiler has no way of knowing that the List
     *       is the only way to access the Nodes, and thus being done with the
     *       List implies being doing with the Nodes. */
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

    (lst->size)++;

    /* NOTE: By taking as argument a pointer to a List, we can modify the List
     *       we were given; we don't need to return a new List. Rather, this
     *       return value is an error code; if, for example, "idx" were out-of-
     *       bounds, we could return non-zero to indicate an error. */
    return 0;
}

/* lstremove: Removes an element from a linked list. */
void *lstremove(List *lst, int idx) {
    return NULL;
}
