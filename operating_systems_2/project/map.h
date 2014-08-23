#ifndef MAP_H
#define MAP_H

#include <pthread.h>
#include <time.h>

#include "statics.h"
#include "snake.h"

class Map {
	int width;
	int height;
public:
	int **map;
	static pthread_mutex_t mutex;
	Map() {}
	Map(int _height, int _width);
	~Map();
	void spawnFood();
	void setItem(int x, int y, int item);
	int getWidth() { return width; }
	int getHeight() { return height; }
	void draw();
};

#endif /* MAP_H */