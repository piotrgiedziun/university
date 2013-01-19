#include "Task.h"
#include "Lifo.h"
#include <time.h>

#pragma once
class Machine
{
private:
	int table_size;
	Task *table;
	Lifo tabu;
	clock_t start_time;
public:
	Machine(void);
	float runningTime();
	void startRunningTime();
	void setTasks(Task * table,int size) ;
	int* start();
	void swap(int,int,int*);
	int countTWT(int* indexAraay);
	int* lookForBestNeighbour(int from, int neighbours_max, const int* order);
	~Machine(void);
	int funkcjaAspirujaca(int minmum,int* kolejnsc);
};

