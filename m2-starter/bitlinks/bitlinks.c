/*
 * NAME: Sanchit Chawla 
 * ID: 5780642 
 */
#include <stdlib.h>
#include <stdio.h>

#include "bitlinks.h"

/* initialize the internal structure of a linked list */
void init(LinkedList *l) {
  l->head  = NULL;
  l->count = 0;
}

/* Insert an element x to index idx which is in between 0 and l->count.
 * Returns FAILED if anything goes wrong, and SUCCESS otherwise.
 */
int insertAtIndex(LinkedList *l, int idx, int x) {

  if (idx > l->count){
      return FAILED;
  }

  Node* curr = l->head; // Temp
  Node* insert = (Node*)malloc(sizeof(Node));
  insert->data = x;
  insert->next = NULL;

  if (idx == 0){
      insert->next = l->head;
      l->head = insert;
      l->count +=1;
      return SUCCESS;
  }

  for (int i = 0;i < idx -1; i++){
       curr = curr->next;  
  }

  insert->next = curr->next;
  curr->next = insert;
  l->count = (l->count) +1;
  return SUCCESS;
}

/* Removes the element at index idx which is in between 0 and l->count - 1
 * If x is not NULL, the data is saved to the address given by x.
 * Returns SUCCESS if the element has been removed, FAILED otherwise.
 */
int removeAtIndex(LinkedList *l, int idx, int *x) {

    if (idx == 1 && l->count == 2){
      free(l->head->next);
      l->count-=1;
      l->head->next = NULL;
      return SUCCESS;

    }

    if (idx > l->count){return FAILED;}

    if (!x) return FAILED;
    Node* curr = l->head; // Temp
    Node* temp;

    if (idx == 0){
        temp = curr->next;
        *x = curr->data;
        l->head = temp;
        free(curr);
        l->count -= 1;
        return SUCCESS;
    }
    
    for (int i = 0; i < idx -1; i++){
        curr = curr->next;
    }
    temp = curr->next->next;
    *x = curr->next->data;
    free(curr->next);
    curr->next = temp;
    l->count-=1;
    return SUCCESS;
}


/* Completely deallocates a linked list.
 * This means deallocating every node in the list.
 *
 * HINT: Call removeAtIndex() repeatedly.
 */
void destroy(LinkedList *l) {
  int a =0;
  while (l->count > 0){
    removeAtIndex(l, 0, &a);
  }
}


/* Returns the number of elements in the list l whose value (the data field)
 * matches bits at all even-numbered bits.  That is to say, the bits at
 * positions 0, 2, 4, .. are the same. Keep in mind the right-most bit is
 * position $0$.  
 */
int countMatchingEvenBits(LinkedList *l, int bits) {
  // TODO: IMPLEMENT ME
  return 0;
}

/* Returns the position in the list (the first node is position 0) whose value
 * (the data field) yields the longest suffix match with bits. Two numbers a and
 * b have a matching suffix of size k if the last k bits (i.e., the
 * least-significant bits) of a are the same as the k least-significant bits of
 * b.  If there are multiple positions with the same suffix size, use the
 * smallest index position.
 */
int longestSuffixMatch(LinkedList *l, int bits) {
  // TODO: IMPLEMENT ME
  return 0;  
}

/* Removes *all* elements whose data matches the first k bits of tag---that is,
 * their k most-significant bits are the same.  The function returns the
 * number of nodes deleted.
 */
int deleteAllMatching(LinkedList *l, int tag, int k) {
  // TODO: IMPLEMENT ME
  return 0;
}



/* Prints out the current list */
void printList(LinkedList *l) {
    printf("LIST> ");
    Node *ptr = l->head;
    while (ptr != NULL) {
        printf("0x%x", ptr->data);
        if (ptr->next) printf(" --> ");
        ptr = ptr->next;
    }
    printf("\n");
}
