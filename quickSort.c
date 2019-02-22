
/*  Wm. Rabe
    Data Structures
    Project 10 - Quick Sort
    2018.12.13
*/

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function prototypes
void print_array(char *[], int);
void quick_sort(char * [], int, int );
int partition(char * [], int, int );
void swap(char *[] , int, int );



int main(int argc, char const *argv[]) {

  // missing arguments filter
  while(!argv[1]){
    printf("Error: Missing argument. Usage: a.exe string\n");
    return 1;
  }


  char ** names;

  // dynamically assigning argv's to names
  for(int i = 0; i < argc; i++){
    names[i] = (char*)malloc(sizeof(char) * (strlen(argv[i]) + 1 ) );
    strcpy(names[i], argv[i]);
  }

  quick_sort(names, 1, argc);
  print_array(names, argc);

  names = NULL; // making sure im returning all memory. freeing names[0] was causing a stack dump
  return 0;
} // end main


// functions
void print_array(char * array[], int size){

  for (size_t i = 1; i < size; i++) {
    printf("%s\n", array[i]);
  }

}// end print_array

void quick_sort(char * array[], int low, int high){
  int p_index;
  if(strcmp(array[low],array[high]) < 0){
    p_index = partition(array, low, high);
    quick_sort(array, low, p_index-1);
    quick_sort(array, p_index+1, high);
  }
} // end quick_sort

int partition(char * array[], int low, int high){
  char * pivot = array[high];
  int p_index = low;
  for (int i = low; i < high; i++) {
    if (strcmp(pivot, array[i]) >= 0){
    swap(array, i, p_index);
    p_index++;
    }
  }
  swap(array, high, p_index);
  return p_index;
} // end partition

void swap(char * a[], int x, int z) {
   char * temp = a[x];
  a[x] = a[z];
  a[z] = temp;
}
