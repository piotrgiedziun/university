#include "snake.h"

#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
#include <vector>

pthread_mutex_t Snake::mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Snake::dead_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Snake::dead = PTHREAD_MUTEX_INITIALIZER;

Snake::Snake(int start_x, int start_y, int length, int _speed, Map *_map) {
	// init snake
	speed = _speed;
	map = _map;
	points = 0;
	dir = 0;
	for(int x = 0; x < length; x++) {
		parts.push_back(SnakePart(start_x+x,start_y));
		map->setItem(start_x+x,start_y,MAP_SNAKE);
	}

	draw(STATUS_OK);
	tick();
}

int Snake::moveTo(int x, int y, SnakePart tail) {
	int status = STATUS_OK;
	pthread_mutex_lock( &(Map::mutex) );

	if( x <= 0 || x >= map->getWidth() || y <= 0 || y >= map->getHeight())
		return STATUS_GAME_OVER;

	int mapItem = map->map[y][x];
	if (mapItem == MAP_WALL || mapItem == MAP_SNAKE) {
		status = STATUS_GAME_OVER;
	} else if(mapItem == MAP_FOOD) {
		status = STATUS_OK_POINT;
		map->map[y][x] = MAP_SNAKE;
	} else {
		map->map[tail.getY()][tail.getX()] = MAP_EMPTY;
		map->map[y][x] = MAP_SNAKE;
	}

	pthread_mutex_unlock( &(Map::mutex) );

	return status;
}

void Snake::tick() {
	// move

	int x=0, y=0;
	SnakePart head = parts.front();

	if( head.getX() <= 0 || head.getX() >= map->getWidth() || head.getY() <= 0 || head.getY() >= map->getWidth()) {
		remove();
		return;
	}

	// set dir
	dir = SNAKE_DIR_TOP;
	
	std::vector<int> dirs;
	if(map->map[head.getY()+1][head.getX()] == MAP_EMPTY) {
		dirs.push_back(SNAKE_DIR_TOP);
	}
	if(map->map[head.getY()-1][head.getX()] == MAP_EMPTY) {
		dirs.push_back(SNAKE_DIR_BOTTOM);
	}
	if(map->map[head.getY()][head.getX()+1] == MAP_EMPTY) {
		dirs.push_back(SNAKE_DIR_RIGHT);
	}
	if(map->map[head.getY()][head.getX()-1] == MAP_EMPTY) {
		dirs.push_back(SNAKE_DIR_LEFT);
	}

	if(dirs.size() != 0)
		dir = dirs[(rand() % dirs.size())];

	// food first!
	if(map->map[head.getY()+1][head.getX()] == MAP_FOOD) {
		dir = SNAKE_DIR_TOP;
	}
	if(map->map[head.getY()-1][head.getX()] == MAP_FOOD) {
		dir = SNAKE_DIR_BOTTOM;
	}
	if(map->map[head.getY()][head.getX()+1] == MAP_FOOD) {
		dir = SNAKE_DIR_RIGHT;
	}
	if(map->map[head.getY()][head.getX()-1] == MAP_FOOD) {
		dir = SNAKE_DIR_LEFT;
	}

	if(dir == SNAKE_DIR_TOP) {
		y+=1;
	}else if(dir == SNAKE_DIR_LEFT) {
		x-=1;
	}else if(dir == SNAKE_DIR_RIGHT) {
		x+=1;
	}else{
		y-=1;
	}
	SnakePart tail = parts.back();

	int restult = moveTo(head.getX()+x, head.getY()+y, tail);
	if( restult == STATUS_OK || restult == STATUS_OK_POINT) {
		// when got point do not remove tail
		if( restult == STATUS_OK_POINT ) {
			parts.push_front(SnakePart(head.getX()+x, head.getY()+y));
		}
		parts.pop_back();
		parts.push_front(SnakePart(head.getX()+x, head.getY()+y));

		// redraw
		redraw(restult, dir);

		// wait
		usleep(100000*speed);
		tick();
	}
	
	remove();
}

void Snake::redraw(int status, int dir) {
	chtype sym;
	if(dir == SNAKE_DIR_TOP) {
		sym = ACS_DARROW;
	}else if(dir == SNAKE_DIR_LEFT) {
		sym = ACS_LARROW;
	}else if(dir == SNAKE_DIR_RIGHT) {
		sym = ACS_RARROW;
	}else{
		sym = ACS_UARROW;
	}

	pthread_mutex_lock( &(mutex) );

	// drew head
	attrset(COLOR_PAIR(COLOR_SNAKE));
	mvaddch((parts.front()).getY(),(parts.front()).getX(), sym);

	// delete taril
	attrset(COLOR_PAIR(COLOR_DEFAUL));
	mvaddch((parts.back()).getY(),(parts.back()).getX(), MAP_NONE_SYM);

	refresh();
	pthread_mutex_unlock( &(mutex) );
}

void Snake::draw(int status) {
	pthread_mutex_lock( &(mutex) );
	attrset(COLOR_PAIR(COLOR_SNAKE));

	std::list<SnakePart>::iterator it;
	for (it = parts.begin(); it != parts.end(); it++) {
		mvaddch((*it).getY(),(*it).getX(), MAP_SNAKE_SYM);
	}

	attrset(COLOR_PAIR(COLOR_DEFAUL));
	mvaddch((parts.back()).getY(),(parts.back()).getX(), MAP_NONE_SYM);

	refresh();
	pthread_mutex_unlock( &(mutex) );
}

void Snake::remove() {
	pthread_mutex_lock( &(Map::mutex) );
	pthread_mutex_lock( &(mutex) );

	attrset(COLOR_PAIR(COLOR_DEFAUL));

	std::list<SnakePart>::iterator it;
	for (it = parts.begin(); it != parts.end(); it++) {
		if(it == parts.begin()) continue;
		map->map[(*it).getY()][(*it).getX()] = MAP_EMPTY;
		mvaddch((*it).getY(),(*it).getX(), MAP_NONE_SYM);
	}

	// remove all excep head
	SnakePart head = parts.front();
	parts.clear();
	parts.push_back(head);
	parts.push_back(head);

	attrset(COLOR_PAIR(COLOR_SNAKE));
	mvaddch(head.getY(),head.getX(), 'D');

	refresh();
	pthread_mutex_unlock( &(Map::mutex) );
	pthread_mutex_unlock( &(mutex) );

	// dead action

	pthread_mutex_lock( &(Snake::dead_mutex) );
		Snake::is_dead = 0;
		pthread_cond_signal(&(Snake::dead)); 

		while( Snake::is_dead == 0 ) {
			Snake::is_dead = 1;
			pthread_cond_wait(&(Snake::dead), &(Snake::dead_mutex));
		}

		Snake::is_dead = 1;		
		//pthread_cond_signal(&(Snake::dead)); 
	pthread_mutex_unlock( &(Snake::dead_mutex) ); 

	tick();
}

void Snake::remove_forever() {
	pthread_mutex_lock( &(Map::mutex) );
	pthread_mutex_lock( &(mutex) );

	attrset(COLOR_PAIR(COLOR_DEFAUL));

	std::list<SnakePart>::iterator it;
	for (it = parts.begin(); it != parts.end(); it++) {
		map->map[(*it).getY()][(*it).getX()] = MAP_EMPTY;
		mvaddch((*it).getY(),(*it).getX(), MAP_NONE_SYM);
	}

	refresh();
	pthread_mutex_unlock( &(Map::mutex) );
	pthread_mutex_unlock( &(mutex) );

	parts.clear();
}
