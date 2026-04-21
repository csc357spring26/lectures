/* Node: Represents an element in a linked list.
 * NOTE: This defines a new type named "struct Node" which is eventually
 *       renamed to "Node", but that renaming will not take effect until after
 *       the structure definition, so we must still use "struct Node" inside
 *       the definition. */
typedef struct Node {
    void *val;
    struct Node *next;
} Node;

/* List: Represents a linked list.
 * NOTE: By grouping these two members into a structure, we can treat them as
 *       a single unit, a new type named "struct List" (which is then renamed
 *       to "List"). Since "struct Node" has already been renamed to "Node", we
 *       can use "Node" inside this definition. */
typedef struct List {
    Node *head;
    int size;
} List;

List *lstcreate(void);
void lstdestroy(List *);
void *lstget(List *, int);
int lstset(List *, int, void *);
int lstadd(List *, int, void *);
void *lstremove(List *, int);
