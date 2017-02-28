/*
 * NAME: Sanchit Chawla
 * ID: 5780642
 */
#include <stdlib.h>
#include <stdio.h>

#include "linkedlist.h"

/* initialize the internal structure of a linked list */
void init(LinkedList *l) {
    
    Node* h = (Node*)malloc(sizeof(Node));
    h->data = (int)malloc(sizeof(int));

    l = (LinkedList)malloc(sizeof(LinkedList));
    l->head = h;
    l-> count = (int)malloc(sizeof(int));
    l->count=0;

}

/* Insert an element x to index idx which is in between 0 and l->count.
 * Returns FAILED if anything goes wrong, and SUCCESS otherwise.
 */
int insertAtIndex(LinkedList *l, int idx, int x) {


    if (idx > count){
        return FAILED;
    }

    // LinkedList proc = (LinkedList)malloc(sizeof(LinkedList));
    // proc->head = l->head;
    // proc-> count = (int)malloc(sizeof(int));
    // proc->count = 0;

    // starts here 
    
    Node* d = (Node*)malloc(sizeof(Node));
    d->data = (int)malloc(sizeof(int));
    d->data = x;

    Node* h = l->head;

    // int c =0;

    // while(head->next!=NULL){

    //     Node* dummy = head->next;

    //     if (idx==c){

    //         dummy->next = dummy;
    //         dummy = d;
    //         // Point the current node to the next
    //         //Put in a node 
    //     }

    //     c++;

    //     dummy = dummy->next;

    // }

    // l->count= l->count + 1;

    int c =0;

    Node* insert;

    while(h->next!=NULL){


        if (c==idx){
            insert = d;
            while(h->next!=NULL){
                h->next = h;    
            }

            h = insert;
            return SUCCESS;
        }

        h = h->next;
        c++;

    }


    return FAILED;


}

/* Removes the element at index idx which is in between 0 and l->count - 1
 * If x is not NULL, the data is saved to the address given by x.
 * Returns SUCCESS if the element has been removed, FAILED otherwise.
 */
int removeAtIndex(LinkedList *l, int idx, int *x) {

    if (idx > count){
        return FAILED;
    }
    

    Node* h = l->head;

    int c =0;


    while(h->next!=NULL){

        if (c==idx){

            while(h->next->!=NULL){

                if (x!=NULL){
                    x = h->data;
                }
                h = h->next;  

            }
        }


        h = h->next;
        c++;

    }


    return SUCCESS;

}

/* Completely deallocates a linked list.
 * This means deallocating every node in the list.
 *
 * HINT: Call removeAtIndex() repeatedly.
 */
void destroy(LinkedList *l) {
    
    free(l->head);
    free(l->count);
    free(l);
}

/* Prints out the current list */
void printList(LinkedList *l) {
    printf("LIST> ");
    Node *ptr = l->head;
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}


/*
EXPECTED OUTPUT:
Insert 1 to index 0. (status: 1)
LIST> 1
Insert 3 to index 0. (status: 1)
LIST> 3 1
Insert 5 to index 5. (status: 0)
LIST> 3 1
Insert 2 to index 1. (status: 1)
LIST> 3 2 1
Insert 4 to index 1. (status: 1)
LIST> 3 4 2 1
Remove 4 from index 1. (status: 1)
LIST> 3 2 1
Remove 3 from index 0. (status: 1)
LIST> 2 1
Remove from index 4. (status: 0)
LIST> 2 1
Remove from index 1. (status: 1)
LIST> 2
Remove 2 from index 0. (status: 1)
LIST>
Insert 99 to index 0. (status: 1)
LIST> 99
After destroying
LIST>
*/
int main() {
    int x, idx, status;
    LinkedList l;

    // Initialize the list
    init(&l);

    // Inserts
    idx = 0;
    x = 1;
    status = insertAtIndex(&l, idx, x);
    printf("Insert %d to index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    idx = 0;
    x = 3;
    status = insertAtIndex(&l, idx, x);
    printf("Insert %d to index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    idx = 5;
    x = 5;
    status = insertAtIndex(&l, idx, x);
    printf("Insert %d to index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    idx = 1;
    x = 2;
    status = insertAtIndex(&l, idx, x);
    printf("Insert %d to index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    idx = 1;
    x = 4;
    status = insertAtIndex(&l, idx, x);
    printf("Insert %d to index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    // Removes
    idx = 1;
    status = removeAtIndex(&l, idx, &x);
    printf("Remove %d from index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    idx = 0;
    status = removeAtIndex(&l, idx, &x);
    printf("Remove %d from index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    idx = 4;
    status = removeAtIndex(&l, idx, &x);
    printf("Remove from index %d. (status: %d)\n", idx, status == SUCCESS);
    printList(&l);

    idx = 1;
    status = removeAtIndex(&l, idx, NULL);
    printf("Remove from index %d. (status: %d)\n", idx, status == SUCCESS);
    printList(&l);

    idx = 0;
    status = removeAtIndex(&l, 0, &x);
    printf("Remove %d from index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    // One more insert
    idx = 0;
    x = 99;
    status = insertAtIndex(&l, idx, x);
    printf("Insert %d to index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    // Destroy
    destroy(&l);
    printf("After destroying\n");
    printList(&l);

}
