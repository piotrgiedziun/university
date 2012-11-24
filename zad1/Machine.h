#include "Task.h"

#pragma once
class Machine
{
private:
	int table_size;
	Task *table;
public:
	Machine(void);
	void setTasks(Task * table,int size) ;
	int* start();
	double calculateP(int* a,int* b,double T);
	int countTWT(int* indexAraay);
	~Machine(void);
};

