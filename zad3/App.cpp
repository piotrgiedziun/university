#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

#include "Task.h"
#include "Machine.h"
#include "Lifo.h"

using namespace std;

const int INSTANCE_SIZE = 50;

void main(int argc, char **argv) {
	// times
	clock_t s, f;

	int *processingTime = new int[INSTANCE_SIZE];
	int *processingWeight = new int[INSTANCE_SIZE];
	int *dueDate = new int[INSTANCE_SIZE];
	int *pointerTable[] = {processingTime, processingWeight, dueDate};

	// task table
	Task *tasks = new Task[INSTANCE_SIZE];

	Machine m;

		ostringstream open_file_name;
		open_file_name << "wt" << INSTANCE_SIZE << ".txt";

		ostringstream save_file_name;
		save_file_name << "o_" << INSTANCE_SIZE << ".txt";

		cout << "outputing to " << save_file_name.str() << endl;

		fstream fs;
		fs.open( save_file_name.str(), std::ios::out );

		ifstream ifs( open_file_name.str() );

		s = clock();
		int count = 0, row = 0, tmpInt;
		while( ifs >> tmpInt ) {

			if(count == INSTANCE_SIZE && row == 2) {

				// create Tasks objects
				for(int i=0; i < INSTANCE_SIZE; i++) {
					tasks[i].setTaskId(i);
					tasks[i].setData(processingTime[i], processingWeight[i], dueDate[i]);
				}

				// start instance
				m.setTasks(tasks, INSTANCE_SIZE);
				int result = m.countTWT(m.start());
				cout << result << endl;
				// show instance result
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
		f = clock();
		fs <<  (double)(f - s) / (double)(CLOCKS_PER_SEC);

		ifs.close();
		fs.close();

	delete[] tasks;

	system("PAUSE");
}