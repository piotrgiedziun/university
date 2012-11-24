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
	this->setParms(10000, 0.1, 0.999);
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
		int tmp= TasksB[to];
		TasksB[to]=TasksB[from];
		TasksB[from]=tmp;

		if(countTWT(TasksB) < countTWT(TasksA))
			memcpy(TasksA,TasksB,sizeof(int)*table_size);

		else if((double) (rand()/(double)(RAND_MAX+1))  < calculateP(TasksA,TasksB,T)) {
			memcpy(TasksA,TasksB,sizeof(int)*table_size);
		}

		T = a*T;
		i +=1;

		//if(countTWT(TasksA) < min) {
		//	min = countTWT(TasksA);
		//}
		//cout << "\tTWT = " << countTWT(TasksA) << endl;
		//system("pause");
	}
	//cout << min << endl;
	return TasksA;
}

double Machine::calculateP(int* a,int* b,double T)
{
	return exp((-(double)(countTWT(b)-countTWT(a)))/T);
}
        //public static int getTasksPower(List<int> index, List<Task> tasks)
        //{
        //    int value = 0;
        //    int cj = 0;
        //    foreach (var i in index)
        //    {
        //        Task t = tasks[i];

        //        cj += t.pj;
        //        int tmp = cj - t.dj;
        //        if (tmp > 0)
        //            value += tmp * t.wj;
        //    }
        //    return value;
        //}

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
