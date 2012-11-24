#include <iostream>
#include <fstream>

#include "Task.h"

using namespace std;

void main(int argc, char **argv) {

	// wczytuje 125 instancji

	// startuje 125 instancji
	
    ifstream ifs("wt40.txt");

	int i;
	while(ifs >> i)
    {
        cout << i << endl;
    }

	system("PAUSE");
}