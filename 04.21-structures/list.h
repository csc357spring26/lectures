/* Node: Represents an element in a linked list. */
void *val;
void *next;

/* List: Represents a linked list. */
void *head;
int size;

List *lstcreate(void);
void lstdestroy(List *);
void *lstget(List *, int);
int lstset(List *, int, void *);
int lstadd(List *, int, void *);
void *lstremove(List *, int);
