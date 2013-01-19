#include "Lifo.h"
#include <vector>

Lifo::Lifo(int max_size, int tasks_size)
{
	this->swaps_max_size = max_size;
	this->tasks_size = tasks_size;
}

void Lifo::poop() {
	this->swaps.pop_back();
}

void Lifo::pusz(int j, int k) {
	if( this->swaps.size() >= this->swaps_max_size )
		this->poop();

	betterPair p; p.j = j; p.k = k;
	this->swaps.push_back(p);
}

HalloType Lifo::hallo_qm(int* order) {
	for(std::vector<betterPair>::iterator it = this->swaps.begin(); it != this->swaps.end(); ++it) {
		betterPair p = (*it);
		for(int i = 0; i < this->tasks_size; i++) {
			if(p.k == order[i]) break;
			if(p.j == order[i]) return HALLO_JESTEM;
		}
	}
	return HALLO_NIE_MA_MNIE;
}

Lifo::~Lifo(void)
{
	this->swaps.clear();
}
