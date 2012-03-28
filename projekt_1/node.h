#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>


using namespace std;

class node {
public:
	int id;
	int d;
	bool v;
	node* p;

	node();
	node(int id);
	operator int(void);
	bool operator > (const node &n) const;
};

typedef vector<node> nodesList;

#endif
