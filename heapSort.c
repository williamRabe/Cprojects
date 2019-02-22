/*  Wm. Rabe
    Data Structures
    Project 10 - Heap Sort
    2018.12.13
*/

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// function prototypes
void print_array(char *[], int);
void max_heapify( char *[], int, int );
void build_max_heap( char *[], int );
void heap_sort( char *[], int );
int right( int );
int left( int );
int parent( int );


int main(int argc, char const *argv[]) {

  // missing arguments filter
  while(!argv[1]){
    printf("Error: Missing argument. Usage: a.exe string\n");
    return 1;
  }


  char ** heap;

  // dynamically assigning argv's to heap
  for(int i = 0; i < argc; i++){
    heap[i] = (char*)malloc(sizeof(char) * (strlen(argv[i]) + 1 ) );
    strcpy(heap[i], argv[i]);
  }

  heap_sort(heap, argc);
  print_array(heap, argc);

  heap = NULL; // making sure im returning all memory. freeing heap[0] was causing a stack dump
  return 0;
} // end main


// functions
void print_array(char * array[], int size){

  for (size_t i = 2; i <= size; i++) {
    printf("%s\n", array[i]);
    free(array[i]);
  }
  free(array[1]);
}// end print_array

void heap_sort( char * array[], int size ){
  build_max_heap( array, size );
  int i = 0;
  char * temp;
  int working_size = size;
  for( i = size; i >= 1; i--){
    temp = array[ 0 ];
    array[0] = array[ i ];
    array[ i ] = temp;
    working_size--;
    max_heapify( array, 0, working_size );
  }
  return;
} // end heap_sort

void build_max_heap( char * array[], int heap_size ){
  int i;
  for( i = (int)floor( heap_size / 2 ); i >= 0; i--){
    max_heapify( array, i, heap_size );
  }
  return;
} // end build_max_heap

void max_heapify(char * array[], int i, int heap_size ){
  int lt = left( i );
  int rt = right( i );
  int largest = 0;
  char * temp;
  if( lt <= heap_size && strcmp(array[ lt ], array[ i ]) > 0){
    largest = lt;
  }else{
    largest = i;
  }

  if( rt <= heap_size && strcmp(array[ rt ], array[ largest ]) > 0){
    largest = rt;
  }

  if( largest != i ){
    temp = array[ i ];
    array[ i ] = array[ largest ];
    array[ largest ] = temp;
    max_heapify( array, largest, heap_size );
  }

} // end max_heapify

int left( int i ){
  return (2*i) + 1;
}

int right( int i ){
  return ( 2*i ) + 2;
}

int parent( int i ){
  return (int) floor( ( i - 1 ) / 2 );
}
