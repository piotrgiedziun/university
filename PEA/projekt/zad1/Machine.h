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
	int* start();
	double calculateP(int* a,int* b,double T);
	void setParms(double T, double Tmin, double a);
	int countTWT(int* indexAraay);
	~Machine(void);
};

