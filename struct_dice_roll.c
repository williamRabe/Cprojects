/*  Wm. Rabe
    Data Structures
    Project 4: Struct Dice Roll
    2018.09.21
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 100
struct roll{
  int dice01;
  int dice02;
};

void print_line(struct roll *, int);
int occurance_counter(struct roll *, int, int);
int random_fill(struct roll *, int);

int main(int argc, char const *argv[]) {

  srand(time(NULL));


  struct roll * array = (struct roll *)malloc(MAX * sizeof(struct roll));

  random_fill(array, MAX);

  printf("Dice Result: Number of Occurrences\n");

  print_line(array, MAX);

  free(array);
  return 0;
}

void print_line(struct roll *ii, int size){

  for(int x = 1; x < 14; x++){
    printf("%-2d was rolled %-2d times\n", x,
      occurance_counter(ii, size, x));
  }
}


int occurance_counter(struct roll * ii, int size, int value){

  int count = 0;
  for(int x = 0; x < size; x++){
    if((ii[x].dice01 + ii[x].dice02) == value){
      ++count;
    }
  }
  return count;
}

int random_fill(struct roll* ii, int size){

  for(int x = 0; x < size; x++){
    ii[x].dice01 = (rand() % 6) + 1;
    ii[x].dice02 = (rand() % 6) + 1;
  }

}
