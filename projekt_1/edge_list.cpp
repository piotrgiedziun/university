#include <vector>
#include <iostream>

#include "node.h"
#include "edge_list.h"

using namespace std;

vector<edge> *edges;

edgesList::edgesList() {}

edgesList::edgesList(int count) {
	edges = new vector<edge>[count];
}

void edgesList::add(node from, node to, int value) {
	edge item;
	item.to = to;
	item.value = value;

	edges[from].push_back(item);
}

bool edgesList::isset(node from, node to) {

	for(vector<edge>::iterator it = edges[from].begin(); it != edges[from].end(); ++it) {
		if((*it).to == to) {
			return true;
		}
	}
	return false;
}

edge edgesList::get(node from, node to) {

	for(vector<edge>::iterator it = edges[from].begin(); it != edges[from].end(); ++it) {
		if((*it).to == to) {
			return *it;
		}
	}

	cout << "error :: edgesList::get :: index out of range (from=" << from << ", to=" << to << ")" << endl;
}

void edgesList::free() {
	delete [] edges;
}

