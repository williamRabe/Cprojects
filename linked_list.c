/*  Wm. Rabe
    Data Structures
    Project 6
    2018.10.12
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
  char ch;
  struct node * next;
  struct node * prev;
};

void print_list(struct node *);
struct node * create_node(char);
struct node * ordered_insert(struct node *, struct node *);
void reverse_list(struct node ** );

void free_list(struct node *);

int main(int argc, char const *argv[]) {
// checking for input string and exits when missing
  while(!argv[1]){
    printf("Error: Missing argument. Usage: a.exe string\n");
    return 1;
  }

  struct node * head = NULL;
  char * buf = NULL;

// building buffer array to feed into list later
  for(int i = 1; i < argc; i++){
    buf = (char *)realloc(buf, strlen(argv[i]));
    strcat(buf, argv[i]);
  }

  // building linked list via loop
  for(int i = 0; i < strlen(buf); i++){
    head = ordered_insert( head, create_node(buf[i]));
  }

  printf("In order A-z:\n");
  print_list(head);


  // reverse linked List
  reverse_list(&head);

  printf("In order z-A:\n");
  print_list(head);

  free_list(head);
  free(buf);
  return 0;
} // end main

void print_list(struct node * head){
  while(head){
    printf("%c ", head->ch);
    head = head->next;
  }
  printf("\n");
} //end print_list

struct node * create_node(char str_element){
	struct node * new_node = ( struct node * )malloc( sizeof( struct node ) );
	new_node->ch = str_element;
	new_node->next = NULL;
	return new_node;
} // end create_node

struct node * ordered_insert( struct node * l_head, struct node * new_node ){

	struct node * current = l_head;

	if( !l_head ){
		return new_node;
	}else{
		while( current->next && new_node->ch >= current->ch){
				current = current->next;
			}
		}
		if( current->prev != NULL && current->ch >= new_node->ch ){
			// We are in the middle of the list.
			new_node->next = current;
			new_node->prev = current->prev;
			current->prev->next = new_node;
			current->prev = new_node;
			return l_head;
		}else if( current->ch >= new_node->ch ){
			// put the new node at the start of the list
			new_node->next = current;
			current->prev = new_node;
			return new_node;
		}else{
			new_node->prev = current;
			current->next = new_node;
			return l_head;
		}
} // end ordered_insert

void reverse_list(struct node ** l_head){
   struct node * temp = NULL;
   struct node * current = *l_head;

   while (current !=  NULL)
   {
     temp = current->prev;
     current->prev = current->next;
     current->next = temp;
     current = current->prev;
   }

   if(temp != NULL )
      *l_head = temp->prev;

} // end ordered_insert

void free_list(struct node * current){
  while(current->next){
    struct node * temp = current;
    current = current->next;
    free(temp);
  }
  if(current == NULL){
    printf("List has been freed.\n");
  }
} // end free_list
