/*
 * DNode.h
 *
 *  Created on: Apr 10, 2013
 *      Author: Ahmed
 */

#ifndef DNODE_H_
#define DNODE_H_
#include <string>
#include <iostream>
#include <vector>
#include "Table_obj.h"

namespace std {

class DNode {
public:
	int id;
	string input;
	vector<Table_obj*> nonDNodes;
	bool isMarked;
	bool isFinalState;
	string pattern;
	string patternName;
	DNode();
	DNode(int x, string y, vector<Table_obj*> z, bool a, bool b,string c,string d);
	virtual ~DNode();
};

} /* namespace std */
#endif /* DNODE_H_ */
