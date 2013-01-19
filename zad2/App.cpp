#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

#include "Task.h"
#include "Machine.h"

using namespace std;

const int INSTANCE_SIZE = 5;

void main(int argc, char **argv) {
	// times
	clock_t s, f;

	// task table
	Task *tasks = new Task[INSTANCE_SIZE];

	// one instance of machine
	Machine m;

	ostringstream open_file_name;
	open_file_name << "data/" << INSTANCE_SIZE << ".txt";

	ostringstream save_file_name;
	save_file_name << "o_" << INSTANCE_SIZE << ".txt";

	cout << "reading " << open_file_name.str() << endl;

	fstream fs;
	fs.open( save_file_name.str(), std::ios::out );

	ifstream ifs( open_file_name.str() );

		s = clock();
		int count = 0, tmpInt[3];

		while( ifs >> tmpInt[0] >> tmpInt[1] >> tmpInt[2] ) {

			cout << tmpInt[0] << " " << tmpInt[1] << " " << tmpInt[2] << endl;

			// create Tasks objects
			tasks[count].setTaskId(count);
			tasks[count].setData(tmpInt[0], tmpInt[1], tmpInt[2]);
			count++;
		}
		f = clock();

		m.setTasks(tasks, INSTANCE_SIZE);
		m.start();
		int result = m.countTWT();

		// show instance result
		fs << result << endl;
		fs <<  (double)(f - s) / (double)(CLOCKS_PER_SEC);

		ifs.close();
		fs.close();

	delete[] tasks;

	system("PAUSE");
}