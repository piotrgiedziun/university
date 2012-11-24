#pragma once

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
	Task(int processingTime, int processingWeight, int dueDate);
	void setData(int processingTime, int processingWeight, int dueDate);
	int getProcessingTime();
	int getProcessingWeight();
	int getDueDate();
	~Task(void);
};

