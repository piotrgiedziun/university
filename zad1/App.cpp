#include <iostream>
#include <fstream>
#include <sstream>

#include "Task.h"
#include "Machine.h"

using namespace std;

int INSTANCE_SIZE = 40;

void main(int argc, char **argv) {

	cout << "start" << endl;

	// !debug mode
	if( INSTANCE_SIZE == 0 ) {
		cout << "instance size= ";
		cin >> INSTANCE_SIZE;
	}

	// temp tables - in order to load data
	int *processingTime = new int[INSTANCE_SIZE];
	int *processingWeight = new int[INSTANCE_SIZE];
	int *dueDate = new int[INSTANCE_SIZE];
	int *pointerTable[] = {processingTime, processingWeight, dueDate};

	// task table
	Task *tasks = new Task[INSTANCE_SIZE];
	// one instance of machine
	Machine m;

	ostringstream file_name;
	file_name << "wt" << INSTANCE_SIZE << ".txt";

	ifstream ifs( file_name.str() );
	int count = 0, row = 0, tmpInt;
	while( ifs >> tmpInt ) {
		if(count == INSTANCE_SIZE && row == 2){

			// create Tasks objects
			for(int i=0; i < INSTANCE_SIZE; i++) {
				tasks[i].setData(processingTime[0], processingWeight[0], dueDate[0]);
			}

			// start instance
			m.setTasks(tasks, INSTANCE_SIZE);
			m.start();

			// show instance result
			cout << "TWT = " << m.countTWT() << endl;

			row = 0;
			count = 0;
		}else if( count == INSTANCE_SIZE ){
			row++;
			count = 0;
		}

		pointerTable[row][count] = tmpInt;

		count++;
    }


	system("PAUSE");
}