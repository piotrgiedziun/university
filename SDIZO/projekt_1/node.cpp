#include "node.h"

node::node() {}

node::node(int id) {
	this->id = id;
	this->d = -1;
	this->v = false;
}

node::operator int(void) {
	return this->id;
}

bool node::operator>(const node &n) const {
	return this->d >= n.d;
}
