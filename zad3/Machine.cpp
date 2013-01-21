#include "Machine.h"
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
	int l=countTWTC((int*)left);
	int r=countTWTC((int*)right);
	return l-r;
}

int* Machine::start() {
	srand(time(NULL));

	this->startRunningTime();

	int min = INT_MAX;
	int populationSize=20;
	int i = 0;
	int reproductionPart=10;
	int mutationPart=3;
	int crossover=populationSize-reproductionPart-mutationPart;

	int** population= new int*[populationSize];
	for(int i=0;i<populationSize;i++)
	{
		population[i]=ranomizeOrder(populationSize);
	}


	min=getMinimumFromPopulation(population,populationSize);

	while(true)
	{

		min=getMinimumFromPopulation(population,populationSize);
		sort(reproductionPart,population,populationSize);


	}


	return ;
}
void Machine::reproduct(int n,int** population,int populationSize,int mutationPart,int crosoverPart)
{
	for(int i=0;i<n;i++)
	{
		if((i+n)<populationSize)
		{
			population[i+n]=population[i];
		}
	}
	for(int i=n;i<n+mutationPart;i++)
	{
		swap(rand()%table_size,rand()%table_size,population[i]);
	}
	int realCrossPart=crosoverPart;
	if(crosoverPart%2!=0)
		realCrossPart--;
	if(realCrossPart==0)
		return;
	for(int i=n+mutationPart;i<n+mutationPart+realCrossPart;i+=2)
	{
		swap(rand()%table_size,rand()%table_size,population[i]);
	}

}
void Machine::crosover(int* first,int*second)
{
	for(int i=table_size/2;i<table_size;i++)
	{
		int j;
		for(j=0;j<i;j++)
		{
			if(first[j]==second[i])
				break;
		}
		if(j==i-1)
			first[i]=second[i];
	}
	for(int i=table_size/2;i<table_size;i++)
	{
		int j;
		for(j=0;j<i;j++)
		{
			if(second[j]==first[i])
				break;
		}
		if(j==i-1)
			second[i]=first[i];
	}

}
void Machine::sort(int n,int** population,int populationSize )
{
	memcpy(population,population,populationSize*sizeof(int*));
	qsort(population,(size_t)populationSize,sizeof(int*),taskComparator);
}
void Machine::swap(int from,int to,int* tasksArray)
{
	int tmp= tasksArray[to];
	tasksArray[to]=tasksArray[from];
	tasksArray[from]=tmp;
}
int Machine::getMinimumFromPopulation(int** population,int populationSize)
{
	int mininimum= countTWT(population[0]);
	for(int i=1;i<populationSize;i++)
	{
		mininimum= min(mininimum,countTWT(population[0]));
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
