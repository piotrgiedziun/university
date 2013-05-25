#include <list>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <list>

#include "statics.h"
#include "snake.h"
#include "map.h"

void* init_snake( void *snake_init_struct );

void spawn_snakes(Map *map, int count, std::list<pthread_t> &threads) {
	for(int i=0; i<count; i++) {
		pthread_t thread;
		threads.push_front(thread);

		// random snake position
		int length = 3+(rand() % 5); // 3-5
		int speed = 2+(rand() % 15);
		int start_x = 1 + (rand() % (map->getWidth()-length-1));

		SnakeInitStruct *sis = new SnakeInitStruct(
			start_x,
			((i+1)*3),
			length,
			speed,
			map
		);

		pthread_create( &thread, NULL, init_snake, (void*) sis);
	}
}

void* init_snake( void *snake_init_struct ) {
	SnakeInitStruct *sis = (SnakeInitStruct*)snake_init_struct;
	Snake *snake = new Snake(sis->start_x, sis->start_y, sis->length, sis->speed, sis->map);
}

void init_color_sets( void ) {
	init_pair(COLOR_DEFAUL, 0, 0);
	init_pair(COLOR_SNAKE, COLOR_YELLOW, COLOR_RED);
	init_pair(COLOR_WALL, COLOR_RED, COLOR_GREEN);
	init_pair(COLOR_FOOD, COLOR_WHITE, 0);
}

int main() {
	// reset for future random usage
	srand ( time(NULL) ); 

	initscr();
	start_color();
	noecho();
	curs_set(0);

	init_color_sets();

	// create threads list
	std::list<pthread_t> threads;

	// create map
	Map *map = new Map(40,40);
	map->draw();

	spawn_snakes(map, 10, threads);
	map->spawnFood();

	while(1) {}
	endwin(); 
}