﻿#pragma once

/**
*	Task
*	p - czas wykonania
*	w - waga
*	d - oczekiwany czas zakończenia
*/

class Task
{
private:
	int p;
	int w;
	int d;

public:
	Task(){};
	Task(int, int, int);
	void setData(int, int, int);
	int getProcessingTime();
	int getProcessingWeight();
	int getDueDate();
	~Task(void);
};

