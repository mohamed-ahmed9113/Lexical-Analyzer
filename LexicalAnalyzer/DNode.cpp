/*
 * DNode.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: Ahmed
 */

#include "DNode.h"

namespace std {

DNode::DNode(int x, string y, vector<Table_obj*> z, bool a, bool b, string c,
		string d) {
	id = x;
	input = y;
	nonDNodes = z;
	isMarked = a;
	isFinalState = b;
	patternName = c;
	pattern = d;
}
DNode::DNode() {
	// TODO Auto-generated destructor stub
}
DNode::~DNode() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */

