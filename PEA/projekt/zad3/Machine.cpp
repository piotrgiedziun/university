﻿#include "Machine.h"
#include "Task.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

int table_sizeC;
Task* tableC;

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


int countTWTC(const int* indexAraay) {
	int value = 0;
	int c = 0, t;

	for (int i=0; i < table_sizeC; i++ ) {
		int index=indexAraay[i];
		c += tableC[index].getProcessingTime();

		t = c - tableC[index].getDueDate();
		if (t > 0)
			value += t * tableC[index].getProcessingWeight();
	}
	return value;
}


int taskComparator( const void *left, const void *right )
{
	int l=countTWTC(*(int**)left);
	int r=countTWTC(*(int**)right);
	return l-r;
}

int* Machine::start() {
	srand(time(NULL));

	this->startRunningTime();

	int* min;
	int populationSize=150;
	int reproductionPart=50;
	int crossoverPart=20;

	int** population= new int*[populationSize];
	for(int i=0;i<populationSize;i++)
	{
		population[i]=ranomizeOrder(table_size);
	}
	countTWT(population[0]);
	int* best;
	min=getMinimumFromPopulation(population,populationSize);
	int i=0;
	int time;
	vector<int> times;
	int sum=0;
	int od=1;
	while(i<5000)
	{
		
		i++;
		int* minT=getMinimumFromPopulation(population,populationSize);
		if(countTWT(minT)<countTWT(min))
		{
			min=minT;
		}
		times.push_back(countTWT(min));
		sum+=times.at(times.size()-1);

		
		sort(reproductionPart,population,populationSize);
		reproduct(reproductionPart,population,populationSize,0,crossoverPart);
		
	}
	return min;
}
void Machine::reproduct(int n,int** population,int populationSize,int mutationPart,int crosoverPart)
{
	for(int i=0;i<n;i++)
	{
		if((i+n)>=populationSize)
			break;
		memcpy( population[i+n], population[i],sizeof(int)*table_size);
	}


	for(int i=n;i<n+crosoverPart-2;i+=2)
	{
		crosover(population[i],population[i+1]);
	}
	for(int i=0;i<populationSize;i++)
	{
		 if(rand()%70==1)
		 {
			this->swap(rand()%table_size,rand()%table_size,population[i]);
			this->swap(rand()%table_size,rand()%table_size,population[i]);
			this->swap(rand()%table_size,rand()%table_size,population[i]);
			this->swap(rand()%table_size,rand()%table_size,population[i]);
			this->swap(rand()%table_size,rand()%table_size,population[i]);
		 }
	}

}

bool Machine::crosover_isset(int stop, int number, int* table) {
	for(int j=0; j<stop; j++)
		if(number==table[j]) 
			return true;
	return false;
}

void Machine::crosover(int* first,int*second) {
	int r = (rand() % (this->table_size-1)) + 1;
	int *of, *os, firstC, secondC;
	of = new int[this->table_size];
	os = new int[this->table_size];

	for(int i=0; i<r; i++) {
		of[i] = first[i];
		os[i] = second[i];
	}

	firstC=secondC=r;

	for(int i=0; i<this->table_size; i++) {
		if(!crosover_isset(r, first[i], second)) {
			os[secondC++] = first[i];
		}
		if(!crosover_isset(r, second[i], first)) {
			of[firstC++] = second[i];
		}
	}

	first = of;
	second = os;
	delete [] os;
	delete [] of;
}
void Machine::sort(int n,int** population,int populationSize )
{
	memcpy(population,population,populationSize*sizeof(int*));
	tableC=table;
	table_sizeC=table_size;
	qsort(population,(size_t)populationSize,sizeof(int*),taskComparator);
	//for (int i =0;i<populationSize;i++)
	//	cout<<countTWT(population[i])<<endl;
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

	for (int i=0; i < table_size; i++ ) {
				
		
		int index=indexAraay[i];
		
		c += table[index].getProcessingTime();
		//cout<<i<<endl;
		//cout<<index<<endl;
		t = c - table[index].getDueDate();
		if (t > 0)
			value += t * table[index].getProcessingWeight();
	}
	return value;
}
int* Machine::getMinimumFromPopulation(int** population,int populationSize)
{
	int* mininimum= population[0];
	for(int i=1;i<populationSize;i++)
	{
		
		if(countTWT(mininimum)>countTWT(population[i]))
			mininimum= population[i];
	}
	return mininimum;
}
int* Machine::ranomizeOrder(int tableSize)
{
	int* tab =new int[tableSize];
	vector<int> order = vector<int>();
	for (int i = 0; i < tableSize; i++)
		order.push_back(i);

	for (int i = 0; i < tableSize; i++) 
	{
		int pos = rand() % order.size();
		tab[i]=order[pos];
		order.erase(order.begin()+pos,order.begin()+pos+1);
	}
	return tab;
}



Machine::~Machine(void)
{
}
