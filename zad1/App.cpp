#include <iostream>
#include <fstream>
#include <sstream>

#include "Task.h"
#include "Machine.h"

using namespace std;

int INSTANCE_SIZE = 0;

void main(int argc, char **argv) {

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

	ostringstream open_file_name;
	open_file_name << "wt" << INSTANCE_SIZE << ".txt";

	ostringstream save_file_name;
	save_file_name << "o_wt" << INSTANCE_SIZE << ".txt";

	fstream fs;
	fs.open( save_file_name.str(), std::ios::out );

	ifstream ifs( open_file_name.str() );

	int count = 0, row = 0, tmpInt;
	while( ifs >> tmpInt ) {

		if(count == INSTANCE_SIZE && row == 2) {

			// create Tasks objects
			for(int i=0; i < INSTANCE_SIZE; i++) {
				tasks[i].setTaskId(i);
				tasks[i].setData(processingTime[i], processingWeight[i], dueDate[i]);
			}

			// start instance
			m.setParms(10000, 0.1, 0.999);
			m.setTasks(tasks, INSTANCE_SIZE);
			
			// show instance result
			int result = m.countTWT(m.start());
			cout << result << endl;
			fs << result << endl;

			row = 0;
			count = 0;
		}else if( count == INSTANCE_SIZE ){
			row++;
			count = 0;
		}

		pointerTable[row][count] = tmpInt;

		count++;
    }

	fs.close();

	system("PAUSE");
}