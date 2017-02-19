/* Name: Sanchit Chawla
 * ID: 5780642
 */
#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

void insert(Node **tree, int val) {

	Node* t = (Node*)malloc(sizeof(Node));
	t->data = val;
	t->left  = NULL;
	t->right = NULL;
    
	if (!(*tree)){
		*tree = (Node *)malloc(sizeof(Node));
		(*tree)->data = (int)malloc(sizeof(int));
		(*tree) = t;
	}


	else{

		if ((*tree)->right != NULL){

			(*tree)->right = t;

		}
		
		else if ((*tree)->left != NULL){

			(*tree)->left = t;

		}

	}

}

void print(Node *tree) {

	printf("%d\n", tree->data);

	Node* left  = tree->left;
	Node* right = tree->right;
	
	while (right!=NULL){

		printf("|- %s\n", tree->right);

		print(right);
	}

	while (left!=NULL){
		printf("|- %s\n", tree->right);
		print(left);

	}

}

void delete(Node *tree) {
    while(tree->left!=NULL){
    	delete(tree->left);
    	free(tree->left);
    	
    }

    while(tree->right!=NULL){
    	delete(tree->right);
    	free(tree->right);
    }
}

Node *lookup(Node ** tree, int val) {

	if ((*tree)->data==val){
		return *tree;
	}
	while((*tree)->right!= NULL){
		lookup((*tree)->right, val);
	}

	while((*tree)->left!= NULL){
		lookup((*tree)->left, val);	
	}

	return NULL;

}


/***** Expected output: *****
7
|-2
  |-1
  |-4
|-10
  |-15
    |-12
      |-11
Found
Not Found
 *****************************/

int main(int argc, char **argv)
{
    Node *root = NULL;
    Node *target = NULL;

    // add nodes
    insert(&root, 7);
    insert(&root, 2);
    insert(&root, 4);
    insert(&root, 10);
    insert(&root, 1);	
    insert(&root, 15);
    insert(&root, 12);
    insert(&root, 11);

    // Lets see how the tree looks
    print(root);

    // Check if 4 in the tree
    target = lookup(&root, 4);
    if (target) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    // Check if 44 in the tree
    target = lookup(&root, 44);
    if (target) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    // Now let's free up the space
    delete(root);
}
