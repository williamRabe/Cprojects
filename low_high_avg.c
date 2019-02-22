/*Author: William Rabe
  Class: Data Structures
  Project: 2 - Low, High, Average
  Date Due: 2018.09.07 */


#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

float find_avg(const char * [], int);
int find_largest_number(const char * [], int, int);
int find_lowest_number(const char * [], int, int);

int main(int argc, char const *argv[]) {

  printf("\nWelcome to Project 2.\n\n");

  while(argc <= 1){
    printf("ERROR: missing arguments. Usage: a.exe x (x = one or more integers) \n");
    return 1;
  }

  float avg = find_avg(argv, argc);
  int high_num = find_largest_number(argv, argc, INT_MIN);
  int low_num = find_lowest_number(argv, argc, high_num);

  printf("Average: %.2f\n", avg);
  printf("Highest Number: %d\n", high_num);
  printf("Lowest Number: %d\n", low_num);

  return 0;
}

float find_avg(const char *raw[], int size){
  float average = 0;
  for(int x = 1; x < size; x++){
    average += atof(raw[x]);
  }
  average = average / (size - 1);
  return average;
}

int find_largest_number(const char *raw[], int size, int highest_number){

  for(int x = 1; x < size; x++){

    if(highest_number < atoi(raw[x])){
      highest_number = atoi(raw[x]);
    }
  }
  return highest_number;
}

int find_lowest_number(const char *raw[], int size, int lowest_number){

  for(int x = 1; x < size; x++){
    if(lowest_number > atoi(raw[x])){
      lowest_number = atoi(raw[x]);
    }
  }
  return lowest_number;
}
