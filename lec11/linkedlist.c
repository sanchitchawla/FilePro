# include <stdio.h>
# include <stdlib.h>
# include "linkedlist.h"

// Need to free if you malloc only 


int initList(linkedlist* l){
	if (!l) return NULL_LIST_LL;

	l->head = NULL;
	l->tail = NULL;
	l->count = 0;

	return SUCCESS_LL;
}

int insertFront(linkedlist* l, void *data){

	if (!l) return NULL_LIST_LL;
	if (!data) return NULL_DATA_LL;

	node *newnode;

	newnode = (node*)malloc(sizeof(node));

	newnode-> next = l->head;
	newnode-> data = data;

	l->head = newnode;
	(l->count)++; 

	// if the list was empty
	if (!l->tail) l->tail = l->head;

	return SUCCESS_LL;
}

int removeFront(linkedlist* l, void **data){

	if (!l) return NULL_LIST_LL;

	if (!l->count) return EMPTY_LIST_LL;

	node* zombie;
	zombie = l->head;

	l->head = zombie->next;
	(l->count)--;

	*data = zombie->data;
	free(zombie);

	if (!l->count) l->tail = NULL;

	return SUCCESS_LL;

}

int destroyList(linkedlist *l){


	void* notused;

	if(!l) return NULL_LIST_LL;

	while (l-> count){
		removeFront(l, &notused);
	}

	return SUCCESS_LL;

}

int insertBack(linkedlist* l, void *data){

	if (!l) return NULL_LIST_LL;
	if (!data) return NULL_DATA_LL;

	node *newnode;

	newnode = (node*)malloc(sizeof(node));

	newnode-> next = l->tail;
	newnode-> data = data;

	l->tail = newnode;
	(l->count)++; 

	// if the list was empty
	if (!l->head) l->head = l->tail;

	return SUCCESS_LL;
}

int removeBack(linkedlist* l, void **data){

	if (!l) return NULL_LIST_LL;

	if (!l->count) return EMPTY_LIST_LL;

	node* zombie;
	zombie = l->tail;

	l->tail = zombie->next;
	(l->count)--;

	*data = zombie->data;
	free(zombie);

	if (!l->count) l->head = NULL;

	return SUCCESS_LL;
}


int main(){

	linkedlist l;
	int one = 1;
	int two = 2;
	int* x;


	if (initList(&l) != SUCCESS_LL){
		printf("Fail to initialize\n");
	}

	// insertFront(&l, &one);
	// insertFront(&l, &two);
	// removeFront(&l, (void **)&x);

	insertBack(&l, &one);
	insertBack(&l, &two);	
	removeBack(&l, (void **)&x);
	printf("data is %d\n", *x);
	removeBack(&l, (void **)&x);
	printf("data is %d\n", *x);

}




