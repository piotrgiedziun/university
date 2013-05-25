#ifndef SNAKE_H
#define SNAKE_H
 
#include <list>

#include "statics.h"
#include "map.h"

class Map;

class SnakePart {
	int x, y;
public:
	SnakePart(int _x, int _y) {
		x = _x;
		y = _y;
	}
	int getX() { return x; }
	int getY() { return y; }
};

struct SnakeInitStruct {
	int start_x;
	int start_y;
	int length;
	int speed;
	Map *map;

	SnakeInitStruct(int _start_x, int _start_y, int _length, int _speed, Map *_map) {
		start_x = _start_x;
		start_y = _start_y;
		length = _length;
		speed = _speed;
		map = _map;
	}
};

class Snake {
	std::list<SnakePart> parts;
	int points;
	int dir;
	int speed;
	Map *map;
public:
	static pthread_mutex_t mutex;
	Snake() {}
	void remove();
	int moveTo(int x, int y, SnakePart tail);
	Snake(int start_x, int start_y, int length, int _speed, Map *_map);
	void tick();
	void draw(int status);
	void redraw(int status, int dir);
};

#endif /* SNAKE_H */