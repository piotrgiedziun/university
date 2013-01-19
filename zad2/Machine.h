#include "Task.h"

#pragma once
class Machine
{
private:
	int table_size;
	Task *table;
	double T;
	double Tmin;
	double a;
public:
	Machine(void);
	void setTasks(Task * table,int size) ;
	void start();
	int countTWT();
	~Machine(void);
};

