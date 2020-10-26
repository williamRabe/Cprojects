// Title  : Address Book Linked List
// Author : Wm. Rabe
// Date   : 2019.09.09

// Description :
/* Address book using a linked list for organization with pointer to node containing data. */

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Structures
  // infoNode will hold contact info like ph. number and address.
  //"type" defines the type of contact info, "value" will hold the actual data.
  // nextInfoNode points to the next contact info for parent entity if it exits
struct infoNode{
    char * type; // Using char pointers instead of fixed-sized arrays for flexability and dinamic memory allocation.
    char * value;
    struct infoNode * nextInfoNode;
};

  // listNode will hold contact name, a pointer to the entities contact information stored in "infoNode" and a pointer to the next contact.
struct listNode{
  char * name;
  struct infoNode * data;
  struct listNode * next;
};

// Prototypes
struct infoNode * createInfoNode(char *, char *);
struct listNode * createListNode(char *, char *, char *);
struct listNode * orderedInsert(struct listNode *, struct listNode *);
void appendInfo(struct listNode *, char *, char *, char *);
void printInfoNode(struct infoNode *);
void printList(struct listNode *);
void freeAll(struct listNode *);

//Main
int main(int argc, char const *argv[]) {

  struct listNode * head = orderedInsert(head,
    createListNode("Dave", "Phone", "918-555-1111"));
  orderedInsert(head, createListNode("Jessica", "Phone", "918-555-2222"));
  orderedInsert(head, createListNode("Theodore", "Phone", "918-555-333"));

  appendInfo(head, "Dave", "Cell", "918-555-1112");
  appendInfo(head, "Theodore", "Address", "123 Imaginary Lane");
  appendInfo(head, "Dave", "Address", "5656 Something Creative Dr");
  printf("\n");
  printList(head);

  freeAll(head);
  return 0;
} // end main

// Functions
struct infoNode * createInfoNode(char * type, char * value){
  struct infoNode * newInfoNode = (struct infoNode * )malloc(sizeof(struct infoNode));
  newInfoNode->type = type;
  newInfoNode->value = value;
  newInfoNode->nextInfoNode = NULL;
  return newInfoNode;
} // end createInfoNode

struct listNode * createListNode(char * name, char * type, char * value){
  struct listNode * newNode = (struct listNode * )malloc(sizeof(struct listNode));
  newNode->name = name;
  newNode->data = createInfoNode(type, value);
  newNode->next = NULL;
  return newNode;
} // end createListNode

struct listNode * orderedInsert(struct listNode * head, struct listNode * newNode){
  struct listNode * curr = head;
  struct listNode * temp;
  if(!head){
    return newNode;
  } else {

    while(curr->next && newNode->name >= curr->name){
      temp = curr;
      curr = curr->next;
    }

    if(curr->name >= newNode->name){
      temp->next = newNode;
      newNode->next = curr;
    } else {
      curr->next = newNode;
    }

  }
} // end orderedInsert

void appendInfo(struct listNode * head, char * name, char * type, char * value){
  // find the correct person in list
  while(strcmp(head->name, name) != 0){
    head = head->next;
  }

// create and set infoHead
  struct infoNode * curr = head->data;

// find end of info list
  while(curr->nextInfoNode){
    curr = curr->nextInfoNode;
  }

// populate data
  curr->nextInfoNode = createInfoNode(type, value);
} // end appendInfo

void printInfoNode(struct infoNode * curr){
  printf("%s: ", curr->type);
  printf("%s, ", curr->value);
  if(curr->nextInfoNode){
    printInfoNode(curr->nextInfoNode);
  }
} // end printInfoNode

void printList(struct listNode * head){
  while(head){
    printf("%s, ", head->name);
    printInfoNode(head->data);
    printf("\n");
    head = head->next;
  }
  printf("\n");
} // end printList

void freeAll(struct listNode * head){
  while(head->next){
    struct listNode * temp = head;
    head = head->next;
    free(temp);
  }

  if(head == NULL){
    printf("List has been freed\n");
  }

} // end freeAll
