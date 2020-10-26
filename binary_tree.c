/*  Wm. Rabe
    alpha Structures
    Project 7
    2018.10.26
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
  char alpha;
  int num;
  struct node * left;
  struct node * right;
};

struct node * insert(struct node * , char );
int count(struct node *);
void traverse(struct node * );
void reverse(struct node * );
void free_all(struct node * );
char find_high(struct node *);
char find_low(struct node *);


int main(int argc, char const *argv[]) {
// checking for input string and exits when missing
  while(!argv[1]){
    printf("Error: Missing argument. Usage: a.exe string\n");
    return 1;
  }

  struct node * root = NULL; // creating an empty tree
  char * buf = NULL;

// building buffer array to feed into tree later
  for(int i = 1; i < argc; i++){
    buf = (char *)realloc(buf, strlen(argv[i]));
    strcat(buf, argv[i]);
  }

  for (size_t i = 0; i < strlen(buf); i++) {
    root = insert(root, buf[i]);
  }

  printf("Binary tree in order (A-z)\n");
  traverse(root);

  printf("Binary tree in reverse order (z-A)\n");
  reverse(root);
  traverse(root);

  printf("Total number of letters entered: %d\n", count(root));

  reverse(root); // puts bst back in original sorted order (small - large)
  printf("Highest letter value : %c\n", find_high(root));
  printf("Lowest letter value : %c\n", find_low(root));

  free(buf);
  free_all(root);
  //free_tree(root);
  return 0;
} // end main

struct node * insert( struct node * tree, char new_char){
	if( !tree ){
		struct node * new_node = (struct node *)malloc( sizeof( struct node ) );
		new_node->alpha = new_char;
    new_node->num = 1;
    new_node->left = NULL;
		new_node->right = NULL;
		return new_node;
	}else{
		if( new_char < tree->alpha ){
			tree->left = insert( tree->left, new_char );
		} else if(new_char > tree->alpha){
      tree->right = insert( tree->right, new_char );
    } else {
      tree->num += 1; // adds 1 to num when char is already in tree.
    }

		return tree;
	}
} // end insert

// inorder traversal that prints
void traverse(struct node * root){
  if(!root){
    return;
  }
    traverse(root->left);
    printf("%c\t%d\n", root->alpha, root->num);
    traverse(root->right);

} // end traverse

void reverse(struct node * root){
  if(!root){
    return;
  }
  struct node * tmp = root->right;
  root->right = root->left;
  root->left = tmp;
  reverse(root->left);
  reverse(root->right);

} // end reverse

int count( struct node * root ){
	if( !root ){
		return 0;
	}
	return count( root->right ) + root->num + count( root->left );
} // ent count

char find_high(struct node * root){
  if(!root){
    return 0;
  } else if(!root->right){
    return root->alpha;
  }

  find_high(root->right);
} // end find_high

char find_low(struct node * root){
  if(!root){
    return 0;
  } else if(!root->left){
    return root->alpha;
  }

  find_low(root->left);
} // end find_low

void free_all(struct node * root){
  if(root){
   free_all(root->left);
   free_all(root->right);
   free(root);
  }
} // end free_all
