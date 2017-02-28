/* Name: Sanchit Chawla
 * ID: 5780642
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "queue.h"

void push(Queue **q, char *word) {
    
    Node* t = (Node*)malloc(sizeof(Node));
    char* wordcpy= (char*)malloc(strlen(word)+ 1);
    strcpy(wordcpy,word);
    t->data = wordcpy;
    t->next = NULL;

    if (!(*q)){
        *q = (Queue*)malloc(sizeof(Queue));
        (*q)->head = t;
        (*q)->tail = t;
    }

    else{

    	(*q)->tail->next = t;		

    	if ((*q)->head == NULL){
    		(*q)->head = t;

    	}

    	(*q)->tail = t;

    }

}

char* pop(Queue *q) {

	if (isEmpty(q)){
		return NULL;
	}

	Node* m = q->head;

	q->head = q->head->next;
	
	char* p = m->data;
	free(m);

	return p;
}

void print(Queue *q) {

    if (!q || q->head==NULL){
        printf("No items\n");
        return;
    }

    Node* nx = q->head;

    while (nx->next != NULL){
        printf("%s\n", nx->data);
        nx = nx->next;

    }
    printf("%s\n", nx->data);
}

int isEmpty(Queue *q) {
    if (!q || (q)->head== NULL){
        return 1; // Not 0 is True
    }

    return 0;
}

void delete(Queue *q) {
    while (!isEmpty(q)) {
       char *item = pop(q);
       free(item);
   }
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
