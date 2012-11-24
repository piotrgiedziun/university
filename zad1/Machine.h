#include "Task.h"

#pragma once
class Machine
{
public:
	Machine(void);
	void setTasks(Task * table,int size) ;
	void start();
	~Machine(void);
};

