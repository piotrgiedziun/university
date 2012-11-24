#include "Machine.h"
#include "Task.h"


Machine::Machine(void)
{
}

void Machine::setTasks(Task *table, int table_size) {
	this->table = table;
	this->table_size = table_size;
}

void Machine::start() {
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
