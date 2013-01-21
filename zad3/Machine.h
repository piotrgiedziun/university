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
	int* ranomizeOrder(int tableSize);
	int* getMinimumFromPopulation(int** population,int populationSize);
	void reproduct(int n,int** population,int populationSize,int mutationPart,int crosoverPart);
	void crosover(int* first,int*second);
	void sort(int n,int** population,int populationSize );
	void swap(int,int,int*);
	int countTWT(const int* indexAraay);
	~Machine(void);
};

