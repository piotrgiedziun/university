#include <pthread.h>
#include <time.h>
#include <ncurses.h>

#include "map.h"

pthread_mutex_t Map::mutex = PTHREAD_MUTEX_INITIALIZER;

Map::Map(int _height, int _width) {
	height = _height;
	width = _width;

	// alocate map
	map = new int*[height];
	for(int y=0; y < height; y++)
		map[y] = new int[width];

	// initialize map - walls
	for(int y=0; y < height; y++) {
		map[y][0] = MAP_WALL;
			for(int x=1; x < width-1; x++)
				map[y][x] = MAP_EMPTY;
		map[y][width-1] = MAP_WALL;
	}
	for(int x=0; x < width; x++) {
		map[0][x] = MAP_WALL;
		map[height-1][x] = MAP_WALL;
	}
}

void Map::spawnFood() {
	int x,y;
	do {
		x = 1 + rand()%(width-1);
		y = 1 + rand()%(height-1);
	}while( map[y][x] != MAP_EMPTY);

	pthread_mutex_lock( &(Snake::mutex) );
	pthread_mutex_lock( &(Map::mutex) );

		attrset(COLOR_PAIR(COLOR_FOOD));
		if( map[y][x] == MAP_EMPTY) {
			map[y][x] = MAP_FOOD;
			mvaddch(y,x, MAP_FOOD_SYM);
		}

	pthread_mutex_unlock( &(Map::mutex) );
	pthread_mutex_unlock( &(Snake::mutex) );


	usleep(1000000);
	spawnFood();
}

void Map::setItem(int x, int y, int item) {
	map[y][x] = item;
}

Map::~Map() {
	for(int y=0; y < height; y++)
		delete[] map[y];

	delete[] map;
}

void Map::draw() {
	// draw wall
	attrset(COLOR_PAIR(COLOR_WALL)); 

	for(int y=0; y < height; y++)
		for(int x=0; x < width; x++)
			if(map[y][x] == MAP_WALL)
				mvaddch(y,x, MAP_WALL_SYM);

	refresh();
}