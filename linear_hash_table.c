/*  Wm. Rabe
    Data Structures
    Project 9: linear Hash Table
    2018.11.30
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// defined global variables
#define SIZE 100

// structs
struct node{
	int key;
	char value;
	int deleted;
};

// functions
void linear_insert( struct node **, int, char );
int linear_probe(int, int, int);
void initialize_table( struct node ** );
void print_table( struct node ** );
void linear_search( struct node **, int);
void linear_delete( struct node **, int);

// main
int main( int argc, char * argv[] ){

	int random_num;
	char random_let;

// create an array of  struct node pointers with 100 elements
	struct node * hash_table[ SIZE ];
	initialize_table( hash_table );

// populate array with 75 randomly created structs, random num 1 to 1000, letter a-z
	for(int i = 0; i < 75; i++){
		random_num = rand() % 1000 +1;
		random_let = rand() % 25 + 97;
		linear_insert(hash_table, random_num, random_let);
	}

	print_table(hash_table);

// search table for all 1000 possible key values
	for(int i = 1; i <= 1000; i++){
		linear_search(hash_table, i);
	}

// delete all elements with even numbered keys
	for(int i = 1; i <= 1000; i++){
		if( i % 2 == 0){
			linear_delete(hash_table, i);
		}
	}

// insert an additional 25 randomly generated structs
for(int i = 0; i < 25; i++){
	random_num = rand() % 1000 +1;
	random_let = rand() % 25 + 97;
	linear_insert(hash_table, random_num, random_let);
}

	print_table(hash_table);

	return 0;
} // end main

void linear_insert( struct node ** table, int key, char value ){

	int i = 0;
	int j = 0;

	struct node * new_node = (struct node *)malloc( sizeof( struct node ) );
	new_node->key = key;
	new_node->value = value;
	new_node->deleted = 0;

	while( i < SIZE ){

		j = linear_probe( key, i, SIZE );
		if( !table[ j ] ){
			table[ j ] = new_node;
			return;

		}else if( table[ j ]->deleted ){

			free( table[ j ] );
			table[ j ] = new_node;
			return;

		}else{
			i++;
		}
	}
}

int linear_probe(int key, int index, int m){
	int sum = 0;
	int i = 0;
	for( i = 0; i < key; i++ ){
		sum += key;
	}
	return (sum+index) % m;
}

void initialize_table( struct node ** table ){
	int i = 0;
	for( i = 0; i < SIZE; i++ ){
		table[ i ] = NULL;
	}
}

void print_table( struct node ** table ){
	int i = 0;
	for( i = 0; i < SIZE; i++ ){
		if( !table[ i ] ){
			printf( "Position %d is empty\n", i );
		}else if( table[ i ]->deleted ){
			printf( "Position %d is deleted\n", i );
		}else{
			printf( "Position %d: key: %d, value: %c\n", i, table[ i ]->key, table[ i ]->value );
		}
	}

}

void linear_search( struct node ** table, int key){

	int i = 0;
	int probes = 0;
	int index = -1;
	int j = 0;

	do{
		j = linear_probe( key, i, SIZE );
		probes++;
		if( table[ j ] && !table[j]->deleted ){

			if(table[j]->key == key ){
				index = j;
				break;
			}else{
				i++;
			}

		}else{
			i++;
		}
	}while( i < SIZE && table[ j ] );

	if( index == -1 ){
		printf( "Key %d is not in the table, probes: %d\n", key, probes );
	}else{
		printf( "Found key %d at index %d after %d probes\n", key, index, probes );
	}

}

void linear_delete( struct node ** table, int key){
	int i = 0;
	int j = 0;
	int probes = 0;
	int index = -1;

	do{
		j = linear_probe( key, i, SIZE );
		probes++;
		if( table[ j ] ){
			if(table[j]->key == key){
				table[ j ]->deleted = 1;
				index = j;
				break;
			}else{
				i++;
			}
		}
	}while( i < SIZE && table[ j ] );

	if( index == -1 ){
		printf( "Key %d is not in table. Probes: %d\n", key, probes );
	}else{
		printf( "Deleted key: %d at index: %d after %d probes\n", key, index, probes );
	}

}
