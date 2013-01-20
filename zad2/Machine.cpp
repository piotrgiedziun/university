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

int Machine::funkcjaAspirujaca(int minmum,int* kolejnosc)
{
	return minmum>countTWT(kolejnosc);
}

int* Machine::lookForBestNeighbour(const int neighbours_max, const int* order, int min, int &j, int &k) {
	// wygeneruj neibours_max sąsiadów, a następnie wybierz jednego
	int* best_solution = new int[this->table_size];
	int well_not_rly = 5; // inc jeśli rozwiązanie nie jest lepsze
	int accept_worse_after = 8;

	for(int i = 0; i < neighbours_max; i++) {
		int to = rand() % this->table_size;
		int from = rand() % this->table_size;
		int* currentOrder = new int[this->table_size];
		memcpy(currentOrder,order,sizeof(int)*table_size);
		swap(from, to, currentOrder);

		if( !this->tabu.hallo_qm(currentOrder) || this->funkcjaAspirujaca(min, currentOrder) || well_not_rly >=  accept_worse_after) {
			if(this->countTWT(currentOrder) < countTWT(order)) {
				j = from; k = to;
				memcpy(best_solution,currentOrder,sizeof(int)*table_size);
				well_not_rly = 0;
			}else{
				well_not_rly++;
			}
		}else{
			well_not_rly++;
		}

		if(well_not_rly == neighbours_max-1) {
			// return random solution
			//int to = rand() % this->table_size;
			//int from = rand() % this->table_size;
			int* currentOrder = new int[this->table_size];
			memcpy(currentOrder,order,sizeof(int)*table_size);
			//swap(from, to, currentOrder);
			return currentOrder;
		}
	}
	return best_solution;
}

int* Machine::start() {
	srand(time(NULL));

	this->startRunningTime();

	int min = INT_MAX;
	int tabu_size_max = 20;
	int time_max = 2;
	int neibours_max = 10;
	int i = 0;
	int bylo = 0;
	int* TasksA= new int[table_size];
	int* TasksB= new int[table_size];

	// losowe rozwiazanie
	for (int i = 0; i < table_size; i++)
	{
		TasksA[i]=i;
		TasksB[i]=i;
	}

	// lista tabu
	this->tabu.set(tabu_size_max, table_size);
	min=countTWT(TasksA);

	while(this->runningTime() < time_max)
	{
		i++;
		int frame= neibours_max/2;
		int tempDroga=min;
		for(int j =0;j<frame;j++)
		{
			int tabu_j, tabu_k;
			TasksB = this->lookForBestNeighbour(neibours_max, TasksB, min, tabu_j, tabu_k);
			if(countTWT(TasksB)<tempDroga)
			{
				tempDroga=countTWT(TasksB);
				if(tempDroga<1.2*min || funkcjaAspirujaca(min,TasksB))
				{
					tabu.pusz(tabu_j, tabu_k);
				}
				frame+=j;
			}
		}
		if(countTWT(TasksB) < min) {
			memcpy(TasksA,TasksB,sizeof(int)*table_size);
			min = countTWT(TasksA);
			bylo = 0;
		}else{
			bylo++;
		}

		if(bylo == neibours_max*2) 
		{
			vector<int> order = vector<int>();
			for (int i = 0; i < table_size; i++)
				order.push_back(i);

			for (int i = 0; i < table_size; i++) {
				int pos = rand() % order.size();
				TasksB[i]=order[pos];
				order.erase(order.begin()+pos,order.begin()+pos+1);
			}
			bylo = 0;
		}

	}

	//for(int i=0; i<this->table_size; i++) {
	//	cout << "order " << this->table[TasksA[i]].getTaskId() << endl;
	//}

	return TasksA;
}

void Machine::swap(int from,int to,int* tasksArray)
{
		int tmp= tasksArray[to];
		tasksArray[to]=tasksArray[from];
		tasksArray[from]=tmp;
}

int Machine::countTWT(const int* indexAraay) {
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
