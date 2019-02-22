/*  Wm. Rabe
    Data Structures
    Project 8 - Implimentation of Graph data structure in form of word based adventure game.
    2018.11.09
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WIDTH 5
#define HEIGHT 3
#define MAX (WIDTH * HEIGHT)

struct room{
	char name[ 32 ];
	int room_number;
  int light;
	// The physical connection between rooms
	struct room * north;
	struct room * south;
	struct room * east;
	struct room * west;
  struct room * up;
  struct room * down;
	// The path between rooms
	int north_path;
	int south_path;
	int east_path;
	int west_path;
  int stairs_up;
  int stairs_down;
	// utility variable.
	int visited;
};
// struct room_list{
//   struct room * n;
//   struct room_list * next;
// };

struct node{
	struct room * room;
	struct node * next;
};

struct player{
	struct room * location;
	int has_torch;
	int eaten_by_grue;
};

struct room * room_constructor( int num, char * );
void construct_rooms( struct room * [], int );
void build_map( struct room * [], int, int );
void connect_rooms( struct room *, struct room * );

void binary_tree_maze( struct room * map[] );
void depth_first_maze( struct room * );
struct room * get_random_room( struct room * );
int unvisited_count( struct room * );
void game(struct room * []);
void describe_room( struct room * , struct player *  );
int check_room( struct player * , struct room *  );
// void depth_first_search(struct room * [], struct room * []);

int main( int argc, char * argv[] ){

	srand( time( NULL ) );

	struct room * map[ MAX ];
	construct_rooms( map, MAX );
	build_map( map, WIDTH, HEIGHT );
	depth_first_maze( map[ 0 ]);
  // depth_first_search( map[0], map[MAX] );

  game(map);


	return 0;
}

// Constructor
struct room * room_constructor( int num, char * given_name ){
	struct room * new_room = (struct room *)malloc( sizeof( struct room ) );
	snprintf( new_room->name, sizeof( new_room->name ), "Room %d", num );
	new_room->room_number = num;
  new_room->light = 0;
	new_room->north = NULL;
	new_room->south = NULL;
	new_room->east = NULL;
	new_room->west = NULL;
  new_room->up = NULL;
  new_room->down = NULL;
	new_room->north_path = 0;
	new_room->south_path = 0;
	new_room->east_path = 0;
	new_room->west_path = 0;
  new_room->stairs_up = 0;
  new_room->stairs_down = 0;

	new_room->visited = 0;
	return new_room;
}

void construct_rooms( struct room * map[], int size ){
	int i = 0;
	for( i = 0; i < size; i++){
		map[ i ] = room_constructor( i+1, "Name: " );
	}
}

void build_map( struct room * map[], int width, int height ){
	int i = 0;
	int x = 0;
	int y = 0;
	for( y = 0; y < height; y++ ){
		for( x = 0; x < width; x++ ){
			map[ i ]->north = (y==0) ? NULL : map[ ( i-width ) ];
			map[ i ]->south = (y==height-1) ? NULL : map[ ( i+width ) ];
			map[ i ]->east = (x==width-1) ? NULL : map[ ( i+1 ) ];
			map[ i ]->west = (x==0) ? NULL : map[ ( i-1 ) ];
			i++;
		}
	}
}

void connect_rooms( struct room * current_room, struct room * next_room ){
	if( current_room->north == next_room ){
		current_room->north_path = 1;
		next_room->south_path = 1;
		return;
	}
	if( current_room->south == next_room ){
		current_room->south_path = 1;
		next_room->north_path = 1;
		return;
	}
	if( current_room->east == next_room ){
		current_room->east_path = 1;
		next_room->west_path = 1;
		return;
	}
	if( current_room->west == next_room ){
		current_room->west_path = 1;
		next_room->east_path = 1;
		return;
	}
  if(current_room->up == next_room){
    current_room->stairs_up = 1;
    next_room->stairs_down = 1;
  }
  if(current_room->down == next_room){
    current_room->stairs_down = 1;
    next_room->stairs_up = 1;
  }
}

void depth_first_maze( struct room * start ){

  int torch_loc = rand() % 5;
	struct room * current_room = start;
	start->visited = 1;
	int rooms_visited = 1;
	struct node * stack = NULL;
	while( rooms_visited < MAX ){
		struct room * next_room = get_random_room( current_room );
		if( next_room ){
			struct node * temp = (struct node *)malloc( sizeof( struct node ) );
			temp->room = current_room;
			temp->next = stack;
			stack = temp;
			connect_rooms( current_room, next_room );
			current_room = next_room;
			current_room->visited = 1;
			rooms_visited++;
		}else if( stack ){
			current_room = stack->room;
			stack = stack->next;
		}
    if(rooms_visited == torch_loc){
      current_room->light = 1;
    }
	}
  printf("Rooms built: %d\n", rooms_visited);

}

// void bredth_first_traversal(struct room * start){
// do a thing - code developed in lecture period begins on line 394. 
// }

struct room * get_random_room( struct room * the_room ){
	struct room * returned_room = NULL;
	int uv = unvisited_count( the_room );
	struct room * directions[ 4 ];
	directions[ 0 ] = NULL;
	directions[ 1 ] = NULL;
	directions[ 2 ] = NULL;
	directions[ 3 ] = NULL;
	int counter = 0;
	if( uv > 0 ){
		if( the_room->north ){
			if( the_room->north->visited == 0 ){
				directions[ counter ] = the_room->north;
				counter++;
			}
		}
		if( the_room->south ){
			if( the_room->south->visited == 0 ){
				directions[ counter ] = the_room->south;
				counter++;
			}
		}
		if( the_room->east ){
			if( the_room->east->visited == 0 ){
				directions[ counter ] = the_room->east;
				counter++;
			}
		}
		if( the_room->west ){
			if( the_room->west->visited == 0 ){
				directions[ counter ] = the_room->west;
				counter++;
			}
		}
		int r = ( rand() % counter );
		returned_room = directions[ r ];
	}
	return returned_room;
}

int unvisited_count( struct room * the_room ){
	int count = 0;
	if( the_room->north ){
		if( the_room->north->visited == 0 ){
			count++;
		}
	}
	if( the_room->south ){
		if( the_room->south->visited == 0 ){
			count++;
		}
	}
	if( the_room->east ){
		if( the_room->east->visited == 0 ){
			count++;
		}
	}
	if( the_room->west ){
		if( the_room->west->visited == 0 ){
			count++;
		}
	}
	return count;
}

void game(struct room * cave[]){
  struct player * p = (struct player *)malloc( sizeof( struct player ) );
  p->location = cave[0];
  p->has_torch = 0;
  p->eaten_by_grue = 0;

  int game_over = 0;

  while( !game_over ){
    describe_room( p->location, p );
    printf( "What is your command: " );
    char user_input = getchar();
    while((getchar()) != '\n');
    switch( user_input ){
      case 'n' :
        if( p->location->north ){
          if( check_room( p, p->location->north ) ){
            p->location = p->location->north;
          }else{
            printf( "You have been eaten by a Grue!\n" );
            p->eaten_by_grue = 1;
            game_over = 1;
          }
        }else{
          printf( "You walked into a wall!\n" );
        }
      break;
      case 's' :
        if( p->location->south ){
          if( check_room( p, p->location->south ) ){
            p->location = p->location->south;
          }else{
            printf( "You have been eaten by a Grue!\n" );
            p->eaten_by_grue = 1;
            game_over = 1;
          }
        }else{
          printf( "You walked into a wall!\n" );
        }
      break;
      case 'e' :
        if( p->location->east ){
          if( check_room( p, p->location->east ) ){
            p->location = p->location->east;
          }else{
            printf( "You have been eaten by a Grue!\n" );
            p->eaten_by_grue = 1;
            game_over = 1;
          }
        }else{
          printf( "You walked into a wall!\n" );
        }
      break;
      case 'w' :
        if( p->location->west ){
          if( check_room( p, p->location->west ) ){
            p->location = p->location->west;
          }else{
            printf( "You have been eaten by a Grue!\n" );
            p->eaten_by_grue = 1;
            game_over = 1;
          }
        }else{
          printf( "You walked into a wall!\n" );
        }
      break;
      case 'u' :
        if( p->location->up ){
          if( check_room( p, p->location->up) ){
            p->location = p->location->up;
          }else{
            printf( "You have been eaten by a Grue!\n" );
            p->eaten_by_grue = 1;
            game_over = 1;
          }
        }else{
          printf( "There aren't stairs here!\n" );
        }
      break;
      case 'd' :
        if( p->location->down ){
          if( check_room( p, p->location->down) ){
            p->location = p->location->down;
          }else{
            printf( "You have been eaten by a Grue!\n" );
            p->eaten_by_grue = 1;
            game_over = 1;
          }
        }else{
          printf( "There aren't stairs here!\n" );
        }
      break;
      case 'q' :
        game_over = 1;
      break;
    }
    // Process Events?
    if( p->location->light == 1 ){
      printf( "You have found a torch!\n" );
      p->has_torch = 1;
    }
    if( p->location == cave[MAX] ){
      printf( "You have escaped!\n" );
      game_over = 1;
    }
    if( p->eaten_by_grue ){
      printf( "You have lost the game!\n" );
      //game_over = 1;
    }
  }
printf( "Thanks for playing!\n" );
}

void describe_room( struct room * room, struct player * p ){
	if( room->light || p->has_torch ){
		printf( "\nYou are in %s\n", room->name );
		if( room->north ) printf( "There is a path to the North\n" );
		if( room->south ) printf( "There is a path to the South\n" );
		if( room->east ) printf( "There is a path to the East\n" );
		if( room->west ) printf( "There is a path to the West\n" );
		if(room->up) printf("There are Stairs leading Up\n");
		if(room->down) printf("There are Stairs leading Down\n");

	}else{
		printf( "It is too dark. You might get eaten by a Grue!\n" );
	}
}

int check_room( struct player * p, struct room * dest ){
	if( dest->light == 0 && p->has_torch == 0 && p->location->light == 0 ){
		return 0;
	}else{
		return 1;
	}
}

// void depth_first_search( struct room * start, struct room * end ){
// 	int found = 0;
// 	struct room_list * stack = (struct room_list *)malloc( sizeof( struct room_list ) );
// 	stack->n = start;
// 	stack->next = NULL;
//
// 	do{
// 		struct room_list * temp = stack;
// 		stack = stack->next;
// 		printf( "Temp is looking at: %s, visited: %d\n", temp->n->name, temp->n->visited );
// 		if( temp->n == end ){
// 			printf( "Depth first found a solution\n" );
// 			found = 1;
// 		}else{
// 			if( !temp->n->visited ){
// 				temp->n->visited = 1;
// 				if( temp->n->north ){
// 					struct room_list * north_temp = (struct room_list *)malloc( sizeof( struct node) );
// 					north_temp->n = temp->n->north;
// 					north_temp->next = stack;
// 					stack = north_temp;gcc
// 				}
// 				if( temp->n->south ){
// 					struct room_list * south_temp = (struct room_list *)malloc( sizeof( struct node) );
// 					south_temp->n = temp->n->south;
// 					south_temp->next = stack;
// 					stack = south_temp;
// 				}
// 				if( temp->n->east ){
// 					struct room_list * east_temp = (struct room_list *)malloc( sizeof( struct node) );
// 					east_temp->n = temp->n->east;
// 					east_temp->next = stack;
// 					stack = east_temp;
// 				}
// 				if( temp->n->west ){
// 					struct room_list * west_temp = (struct room_list *)malloc( sizeof( struct node) );
// 					west_temp->n = temp->n->west;
// 					west_temp->next = stack;
// 					stack = west_temp;
// 				}
// 			}
// 		}
// 	}while( stack && !found );
// 	if( !found ){
// 		printf( "Depth first search: no solution found" );
// 	}
//
// }
