#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define SUCCESS 1
#define FAILED -1

struct node_t {
    int data;
    struct node_t *next;
};

typedef struct node_t Node;

struct linkedlist_t {
    Node *head;
    int count;
};

typedef struct linkedlist_t LinkedList;

/* initialize the internal structure of a linked list */
void init(LinkedList *l);

/* Insert an element x to index idx which is in between 0 and l->count.
 * Returns FAILED if anything goes wrong, and SUCCESS otherwise.
 */
int insertAtIndex(LinkedList *l, int idx, int x);

/* Removes the element at index idx which is in between 0 and l->count - 1
 * If x is not NULL, the data is saved to the address given by x.
 * Returns SUCCESS if the element has been removed, FAILED otherwise.
 */
int removeAtIndex(LinkedList *l, int idx, int *x);

/* Completely deallocates a linked list.
 * This means deallocating every node in the list.
 */
void destroy(LinkedList *l);

/* Prints out the current list */
void printList(LinkedList *l);

#endif /*LINKEDLIST_H*/
