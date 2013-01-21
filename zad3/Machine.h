#include "Task.h"
#include "Lifo.h"
#include <time.h>

#pragma once
class Machine
{
private:
	int table_size;
	Task *table;
	clock_t start_time;
public:
	Machine(void);
	float runningTime();
	void startRunningTime();
	void setTasks(Task * table,int size) ;
	int* start();
	int* Machine::ranomizeOrder(int tableSize);
	int Machine::getMinimumFromPopulation(int** population,int populationSize);
	void swap(int,int,int*);
	int countTWT(const int* indexAraay);
	~Machine(void);
};

