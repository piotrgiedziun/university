#include "Lifo.h"
#include <vector>
#include <iostream>

Lifo::Lifo(int max_size, int tasks_count)
{
	this->orders_max_size = max_size;
	this->order_tasks_count = tasks_count;
}

void Lifo::poop() {
	this->orders.pop_back();
}

void Lifo::pusz(int* order) {
	if( this->orders.size() >= this->orders_max_size-1 )
		this->poop();

	this->orders.push_back(order);
}

HalloType Lifo::hallo_qm(int* order) {
	for(std::vector<int*>::iterator it = this->orders.begin(); it != this->orders.end(); ++it) {
		for(int i = 0; i < this->order_tasks_count; i++) {
			std::cout << (*it)[i] << " " << order[i] << std::endl;
			if( (*it)[i] != order[i] ) 
				continue;
			return HALLO_JESTEM;
		}
	}
	return HALLO_NIE_MA_MNIE;
}

Lifo::~Lifo(void)
{
	this->orders.clear();
}
