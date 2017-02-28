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

		(*tree) = t;

	}

	else{

		Node* curr = (*tree);
		Node* child;

		while(1){

			if (val > curr->data){
				child = curr->right;

				if (curr->right==NULL){
					curr->right = t;
					break;	
				}
				curr = child;
			}
			
			else if (val < curr->data){
				child = curr->left;
				
				if (curr->left==NULL){
					curr->left = t;	
					break;
				}
				curr = child;				
			}

		}

	}

}

void helpmeprint(Node *tree, int deep){


	if (tree==NULL){
		return;
	}

	for (int i = 0; i < deep -1; i++){
		printf("  ");
	}

	printf("|-");
	printf("%d\n", tree->data);
	helpmeprint(tree->left,deep+1);
	helpmeprint(tree->right,deep+1);
	


}


void print(Node *tree) {

	if (!tree){
		return;
	}

	printf("%d\n", tree->data);

	helpmeprint(tree->left, 1);
	helpmeprint(tree->right, 1);

}




void delete(Node *tree) {

	if (tree==NULL){
		return;
	}

    if (tree->left){
    	delete(tree->left);
    }

    if(tree->right){
    	delete(tree->right);
    }
    
    free(tree);
}

Node *lookup(Node ** tree, int val) {

	Node* curr = (*tree);
	Node* child;

	while(1){

		if (val > curr->data){
			if (curr->right==NULL){
				return NULL;
			}
			child = curr->right;
			curr = child;
		}
		else if (val < curr->data){
			if (curr->left==NULL){
				return NULL;
			}
			child = curr->left;
			curr = child;
		}
		if (curr->data==val){
			return curr;
		}

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
