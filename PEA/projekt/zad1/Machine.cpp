#include "Machine.h"
#include "Task.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

using namespace std;

Machine::Machine(void)
{

}

void Machine::setParms(double T, double Tmin, double a) {
	this->T = T;
	this->Tmin = Tmin;
	this->a = a;
}

void Machine::setTasks(Task *table, int table_size) {
	this->table = table;
	this->table_size = table_size;
}

int* Machine::start() {
	srand(time(NULL));
	int min = INT_MAX;
	int i = 0;
	int* TasksA= new int[table_size];
	int* TasksB= new int[table_size];
	for (int i = 0; i < table_size; i++)
	{
		TasksA[i]=i;
	}
	while(T > Tmin)
	{
		memcpy(TasksB,TasksA,sizeof(int)*table_size);
		int from =rand()%table_size;
		int to=rand()%table_size;
		swap(from,to,TasksB);
		if(countTWT(TasksB) < countTWT(TasksA))
			memcpy(TasksA,TasksB,sizeof(int)*table_size);

		else if((double) (rand()/(double)(RAND_MAX+1))  < calculateP(TasksA,TasksB,T)) {
			memcpy(TasksA,TasksB,sizeof(int)*table_size);
		}

		T = a*T;
		i++;
	}
	return TasksA;
}
void swap(int from,int to,int* tasksArray)
{
		int tmp= tasksArray[to];
		tasksArray[to]=tasksArray[from];
		tasksArray[from]=tmp;
}

double Machine::calculateP(int* a,int* b,double T)
{
	return exp((-(double)(countTWT(b)-countTWT(a)))/T);
}

int Machine::countTWT(int* indexAraay) {
	int value = 0;
	int c = 0, t;

	for (int i=0; i < this->table_size; i++ ) {
		int index=indexAraay[i];
		c += table[index].getProcessingTime();

		t = c - table[index].getDueDate();
		if (t > 0)
			value += t * table[index].getProcessingWeight();
	}
	return value;
}

Machine::~Machine(void)
{
}
