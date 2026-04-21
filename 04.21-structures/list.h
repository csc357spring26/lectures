/* Node: Represents an element in a linked list.
 * NOTE: Here, we define the new type "struct Node", which will eventually be
 *       renamed "Node", but the compiler is only aware of "struct Node" inside
 *       the definition. Note that a Node cannot contain another Node (which
 *       would be infinitely recursive), but it can contain a pointer. */
typedef struct Node {
    void *val;
    struct Node *next;
} Node;

/* List: Represents a linked list.
 * NOTE: Just like a class in an object-oriented language, a structure defines
 *       a new type by composing related variables, its "members", which we can
 *       treat as a single unit. Unlike a class, a structure may not contain
 *       any methods. */
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
