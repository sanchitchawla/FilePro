#include<stdio.h>
#include"bitlinks.h"

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

    idx = 0;
    status = removeAtIndex(&l, idx, &x);
    printf("Remove %d from index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);


    idx = 0;
    x = 0x111;
    status = insertAtIndex(&l, idx, x);
    printf("Insert %d to index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    idx = 0;
    x = 0x67b;
    status = insertAtIndex(&l, idx, x);
    printf("Insert %d to index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    idx = 2;
    x = 0x73b;
    status = insertAtIndex(&l, idx, x);
    printf("Insert %d to index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);


    idx = 2;
    x = 0x57b;
    status = insertAtIndex(&l, idx, x);
    printf("Insert %d to index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    // l:   0x67b --> 0x111 --> 0x57b --> 0x73b
    printf("longestSuffixMatch(l, 0x77b) == %d\n", longestSuffixMatch(&l, 0x77b));

    idx = 1;
    x = 0x711;
    status = insertAtIndex(&l, idx, x);
    printf("Insert %d to index %d. (status: %d)\n", x, idx, status == SUCCESS);
    printList(&l);

    
    printf("longestSuffixMatch(l, 0x311) == %d\n", longestSuffixMatch(&l, 0x311));
    
    printf("countMatchingEvenBits(l, 0xbbb) == %d\n", countMatchingEvenBits(&l, 0xbbb));

    int tag = 0x600;
    status = deleteAllMatching(&l, tag, 23);
    printf("deleteAllMatching(l, 0x%x, %d) == %d\n", tag, 23, status);
    printList(&l);
    
    // Destroy
    destroy(&l);
    printf("After destroying\n");
    printList(&l);

}
