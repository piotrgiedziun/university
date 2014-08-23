#ifndef EDGE_LIST_H
#define EDGE_LIST_H

#include "node.h"

struct edge {
	node value;
	node to;
};

class edgesList {
public:
	edgesList();
	edgesList(int count);
	void add(node from, node to, int value);
	edge get(node from, node to);
	bool isset(node from, node to);
	void free();
};

#endif
