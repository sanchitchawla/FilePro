#ifndef _BITLINKS_H__
#define _BITLINKS_H__

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

/* Returns the number of elements in the list l whose value (the data field)
 * matches bits at all even-numbered bits.  That is to say, the bits at
 * positions 0, 2, 4, .. are the same. Keep in mind the right-most bit is
 * position $0$.  
 */
int countMatchingEvenBits(LinkedList *l, int bits);


/* Returns the position in the list (the first node is position 0) whose value
 * (the data field) yields the longest suffix match with bits. Two numbers a and
 * b have a matching suffix of size k if the last k bits (i.e., the
 * least-significant bits) of a are the same as the k least-significant bits of
 * b.  If there are multiple positions with the same suffix size, use the
 * smallest index position.
 */
int longestSuffixMatch(LinkedList *l, int bits);


/* Removes *all* elements whose data matches the first k bits of tag---that is,
 * their k most-significant bits are the same.  The function returns the
 * number of nodes deleted.
 */
int deleteAllMatching(LinkedList *l, int tag, int k);


/* Completely deallocates a linked list.
 * This means deallocating every node in the list.
 */
void destroy(LinkedList *l);

/* Prints out the current list */
void printList(LinkedList *l);

#endif 
