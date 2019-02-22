/*Wm. Rabe
  Data Structures
  Project 5
  2018.09.28
*/

#include <stdio.h>
#include <stdlib.h>
#include<time.h>


struct node{
  int num;
  struct node * next;
};

struct node * push_rand(struct node *);
struct node * pop(struct node *);
struct node * enqueue(struct node *, struct node *);
struct node * dequeue(struct node *, struct node *);
void print_node(struct node *);
void print_list(struct node *);


int main(int argc, char const *argv[]) {

  struct node * head = NULL;
  struct node * tail = NULL;
  srand(time(NULL));

  print_list( head );

  // push random int to 6 nodes
  for (size_t i = 0; i < 6; i++) {
    head = push_rand( head );
    printf("Push: %d\n", head->num);
  }

  print_list( head );

  // pop list
  for (size_t i = 0; i < 6; i++) {
    head = pop( head );
  }

  print_list( head );
  head = tail = NULL;

  // enqueue random int to 6 nodes
  for (size_t i = 0; i < 6; i++) {
    tail = enqueue( head, tail);
    if(head == NULL){
      head = tail;
    }
    printf("enqueue: %d\n", tail->num);
  }

  print_list( head );

  // dequeue list
  while(head != NULL){
    printf("dequeue: %d\n", head->num);
    head = dequeue( head, tail );
  }

  print_list( head );

  return 0;
}


void print_node( struct node * current ){
	if( current){
		printf( "%d ", current->num);
	}
}

void print_list( struct node * current ){
  printf("\nPrinting List:\n");
  while( current ){
    print_node( current );
    current = current->next;
	}
  printf("\n\n");
}

struct node * push_rand(struct node * root){
  struct node * new_node = (struct node *)malloc( sizeof( struct node ) );
  new_node->num = (rand() % 5) + 1;
  new_node->next = root;
  return new_node;

}

struct node * pop(struct node * current){
  printf("Pop: %d\n", current->num);
  struct node * temp;
  temp = current;
  current = current->next;
  free(temp);
  return current;

}

struct node * enqueue(struct node * head, struct node * tail){
  struct node * new_node = (struct node *)malloc( sizeof( struct node ) );
  new_node->num = (rand() % 5) + 1;
  new_node->next = NULL;
  if(head == NULL && tail == NULL){
    return new_node;
  }

  tail->next = new_node;
  return new_node;
}

struct node * dequeue(struct node * head, struct node * tail){
  struct node * temp = head;
  if(head == NULL){return NULL;}
  head = head->next;
  free(temp);
  return(head);
}
