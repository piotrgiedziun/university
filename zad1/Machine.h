#include "Task.h"

#pragma once
class Machine
{
public:
	Machine(void);
	void setTasks(Task *);
	void start();
	~Machine(void);
};

