#ifndef LISTA_NASTEPNIKOW_H
#define LISTA_NASTEPNIKOW_H

#include <iostream>

using namespace std;

class nastepnik {

public:
	int id;
	int d;
	nastepnik* n;

	nastepnik() {}
	nastepnik(int id, int d){
		this->id = id;
		this->d = d;
		this->n = NULL;
	}
	operator int(void) {
		return this->id;
	}

};

#endif
