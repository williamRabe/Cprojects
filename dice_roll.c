/*  Wm. Rabe
    Data Structures
    Project 3: Dice Roll
    2018.09.14
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print_array(int *, int);
void print_line(int *, int);
int occurance_counter(int *, int, int);
int random_fill(int *, int);
int get_int(void);

int main(int argc, char const *argv[]) {


  int input;
  srand(time(NULL));

  printf("\nPlease enter a number:");
  scanf("%d", &input);

  int * array = (int *)malloc(input * sizeof(int));

  random_fill(array, input);

  print_array(array, input);

  printf("\n\n");

  print_line(array, input);

  free(array);
  return 0;
}


void print_array(int * ii, int size){
  int x = 0;
  while(ii[x] && x < size){
    printf("%d\t", ii[x]);
    x++;
    if((x % 5) == 0){
      printf("\n");
    }
  }

}

void print_line(int *ii, int size){

  for(int x = 1; x < 14; x++){
    printf("%-2d was rolled %-2d times\n", x,
      occurance_counter(ii, size, x));
  }
}


int occurance_counter(int * ii, int size, int value){

  int count = 0;
  for(int x = 0; x < size; x++){
    if(ii[x] == value){
      ++count;
    }
  }
  return count;
}

int random_fill(int * ii, int size){

  for(int x = 0; x < size; x++){
    ii[x] = (rand() % 11) + 2;
  }

}
