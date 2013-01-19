#pragma once

#include <vector>

enum HalloType { HALLO_NIE_MA_MNIE = 0, HALLO_JESTEM = 1};

class Lifo
{
private:
	std::vector<int*> orders;
	int orders_size;
	int orders_max_size;
	int order_tasks_count;
public:
	Lifo(int max_size, int tasks_count);
	~Lifo(void);
	void pusz(int* order);
	void poop();
	HalloType hallo_qm(int* order);
};

