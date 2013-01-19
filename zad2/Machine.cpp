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

void Machine::setTasks(Task *table, int table_size) {
	this->table = table;
	this->table_size = table_size;
}

void Machine::start() {
	srand(time(NULL));
	
}


int Machine::countTWT() {
	int value = 0;
	int c = 0, t;

	for (int i=0; i < this->table_size; i++ ) {
		c += table[i].getProcessingTime();

		t = c - table[i].getDueDate();
		if (t > 0)
			value += t * table[i].getProcessingWeight();
	}
	return value;
}

Machine::~Machine(void)
{
}
