#include "Task.h"

Task::Task(int processingTime, int processingWeight, int dueDate) {
	this->p = processingTime;
	this->w = processingWeight;
	this->d = dueDate;
}

void Task::setData(int processingTime, int processingWeight, int dueDate) {
	this->p = processingTime;
	this->w = processingWeight;
	this->d = dueDate;
}

void Task::setTaskId(int id) {
	this->id = id;
}

int Task::getTaskId() {
	return this->id;
}

int Task::getProcessingTime() {
	return this->p;
}

int Task::getProcessingWeight(){
	return this->w;
}

int Task::getDueDate(){
	return this->d;
}

Task::~Task(void)
{
}
