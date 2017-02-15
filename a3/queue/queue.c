/* Name:
 * ID:
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "queue.h"

void push(Queue **q, char *word) {
    Node* t = (Node*)malloc(sizeof(Node));
    char* wordcpy= (char*)malloc(sizeof(char)*2);
    strcpy(wordcpy,word);
    t->data = wordcpy;
    t->next = (*q)->tail;
    printf("poop\n");

    if (!q){
        printf("in if \n");
        *q = (Queue*)malloc(sizeof(Queue));
        (*q)->head = NULL;
        (*q)->tail = NULL;
        printf("outta print\n");
    }

    (*q)->tail = t;
}

char* pop(Queue *q) {

    if (!q){return NULL;}

    /* Node* h = q->head; */

    q-> tail = q-> head;


    q-> head = NULL;

}

void print(Queue *q) {

    if (!q){
        printf("No items\n");
        return;
    }

    Node* nx = q->head;

    while (nx->next != NULL){
        printf("%s\n", nx->data);
        nx = nx->next;
    }
}

int isEmpty(Queue *q) {
    if (!q){
        return !0;
    }
}

void delete(Queue *q) {
    // IMPLEMENT
}

/***** Expected output: *****
No items
a
b
c
a
b
c
d
e
f
No items
s = World
t = Hello
*****************************/
int main(int argc, char **argv)
{
    Queue *q = NULL;

    // print the queue
    print(q);

    // push items
    printf("in main\n");
    push(&q, "a");
    push(&q, "b");
    push(&q, "c");
    print(q);

    // pop items
    while (!isEmpty(q)) {
        char *item = pop(q);
        printf("%s\n", item);
        free(item);
    }

    char *item = pop(q);
    assert(item == NULL);

    // push again
    push(&q, "d");
    push(&q, "e");
    push(&q, "f");
    print(q);

    // destroy the queue
    delete(q);

    // print again
    print(q);

    // check copy
    char *s = (char *)malloc(10);
    strcpy(s, "Hello");
    push(&q, s);
    strcpy(s, "World");
    char *t = pop(q);
    printf("s = %s\n", s);
    printf("t = %s\n", t);
    free(t);
    free(s);

    // free the queue
    free(q);
}
