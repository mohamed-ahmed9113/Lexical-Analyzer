/*
 * ExpressionEvaluator.h
 *
 *  Created on: 8 Apr 2013
 *      Author: Mohamed
 */

#ifndef EXPRESSIONEVALUATOR_H_
#define EXPRESSIONEVALUATOR_H_
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Table_obj.h"
#include "Lists.h"
using namespace std;

class ExpressionEvaluator {
public:
	ExpressionEvaluator();
	virtual ~ExpressionEvaluator();
	void evaluate();
	void initiateOperand(string val,int i , int j);
	void addTransation(int start , int end , string value);
	void drawStar(Expression_obj exp,int i , int j);
	void drawPlus(Expression_obj exp,int i , int j);
	void drawOr(Expression_obj exp1,Expression_obj exp2,int i , int j);
	void drawConcatenation(Expression_obj exp1,Expression_obj exp2,int i , int j);
	 void add_rows(int number_of_rows);
	Lists l;
	int currentState;
    vector <vector <Table_obj> > table;
    vector <vector <Table_obj*> > NFA;
    vector <int> finalStates;
    vector <string> inputs;
};

#endif /* EXPRESSIONEVALUATOR_H_ */
