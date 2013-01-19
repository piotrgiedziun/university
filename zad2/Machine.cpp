#include "Machine.h"
#include "Task.h"
#include "Lifo.h"
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

void Machine::setTasks(Task *table, int table_size) {
	this->table = table;
	this->table_size = table_size;
}

float Machine::runningTime() {
	return ((float)clock() - (float)this->start_time)/CLOCKS_PER_SEC;
}

void Machine::startRunningTime() {
	this->start_time = clock();
}

+int Machine::funkcjaAspirujaca(int minmum,int* kolejnosc)
+{
+	return minmum>countTWT(kolejnosc);
+}


int* Machine::start() {
	srand(time(NULL));

	this->startRunningTime();

	int min = INT_MAX;
	int tabu_size_max = 5;
	int time_max = 10;
	int i = 0;
	int* TasksA= new int[table_size];
	int* TasksB= new int[table_size];

	// losowe rozwiazanie
	for (int i = 0; i < table_size; i++)
	{
		TasksA[i]=i;
	}

	// lista tabu
	Lifo tabu(tabu_size_max, table_size);

	while(this->runningTime() < time_max)
	{
		memcpy(TasksB,TasksA,sizeof(int)*table_size);
		int from =rand()%table_size;
		int to=rand()%table_size;
		swap(from,to,TasksB);

		if(countTWT(TasksB) < countTWT(TasksA))
			memcpy(TasksA,TasksB,sizeof(int)*table_size);


		i++;
	}
	return TasksA;
}

void Machine::swap(int from,int to,int* tasksArray)
{
		int tmp= tasksArray[to];
		tasksArray[to]=tasksArray[from];
		tasksArray[from]=tmp;
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
