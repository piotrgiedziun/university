#pragma once

#include "Task.h"
#include <vector>

enum HalloType { HALLO_NIE_MA_MNIE = 0, HALLO_JESTEM = 1};
struct betterPair { int j; int k; };

class Lifo
{
private:
	std::vector<betterPair> swaps;
	int swaps_max_size;
	int tasks_size;
public:
	Lifo(int max_size, int tasks_size);
	~Lifo(void);
	void pusz(int j, int k);
	void poop();
	HalloType hallo_qm(int* order);
};

