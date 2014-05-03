/*
 * ExpressionEvaluator.cpp
 *
 *  Created on: 8 Apr 2013
 *      Author: Mohamed
 */

#include "ExpressionEvaluator.h"

ExpressionEvaluator::ExpressionEvaluator() {
	// TODO Auto-generated constructor stub
	l.ini_lists();
	currentState = 1;
	for (unsigned int i = 0; i < l.final_RES.size(); i++) {
		for (unsigned int j = 0; j < l.final_RES[i].size(); j++) {
			cout << l.final_RES[i][j].value << endl;
		}
	}
	evaluate();

}

ExpressionEvaluator::~ExpressionEvaluator() {
	// TODO Auto-generated destructor stub
}

void ExpressionEvaluator::evaluate() {

	for (unsigned int i = 0; i < l.final_RES.size(); i++) {
		unsigned int j = 0;
		for (; j < l.final_RES[i].size(); j++) {
			Expression_obj b = l.final_RES[i][j];
			if (b.type.compare("operand") == 0) {
				initiateOperand(b.value, i, j);

			}

			else {
				if (b.value.compare("*") == 0) {
					drawStar(l.final_RES[i][j - 1], i, j);
					j = j - 1;
				} else if (b.value.compare("+") == 0) {
					drawPlus(l.final_RES[i][j - 1], i, j);
					j = j - 1;
				} else if (b.value.compare("|") == 0) {
					drawOr(l.final_RES[i][j - 1], l.final_RES[i][j - 2], i, j);
					j = j - 2;
				} else {
					drawConcatenation(l.final_RES[i][j - 2],
							l.final_RES[i][j - 1], i, j);
					j = j - 2;
				}

			}

		}
		addTransation(0, l.final_RES[i][0].start, "epsilon");
		finalStates.push_back(l.final_RES[i][0].end);  /// the new line

	}

	vector<Table_obj> v;
	table.push_back(v);
	/*
	 * move to vector of pointers
	 */
	unsigned i;
	unsigned j;
	for (i = 0; i < table.size(); i++) {
		vector<Table_obj*> trans;
		for (j = 0; j < table[i].size(); j++) {
			Table_obj* node = new Table_obj(table[i][j].state,
					table[i][j].value);
			trans.push_back(node);
		}
		NFA.push_back(trans);
	}
}

void ExpressionEvaluator::initiateOperand(string val, int i, int j) {

	if (val.compare("\\L") == 0)
		val = "epsilon";
	addTransation(currentState, currentState + 1, val);
	l.final_RES[i][j].start = currentState;
	l.final_RES[i][j].end = currentState + 1;
	currentState += 2;

}

void ExpressionEvaluator::addTransation(int start, int end, string value) {

	string v = l.remove_slash(value);
	//////////////////////////if not found
	if (value != "epsilon") {
		bool flag = false;
		for (int i = 0; i < inputs.size(); i++) {
			if (inputs[i].compare(v) == 0) {
				flag = true;
				break;
			}
		}
		if (!flag)
			inputs.push_back(v);
	}
	Table_obj t(end, v);
	if (start > table.size())
		add_rows(start - table.size() + 1);

	table[start].push_back(t);

}
void ExpressionEvaluator::drawOr(Expression_obj exp1, Expression_obj exp2,
		int i, int j) {
	int start1 = exp1.start;
	int end1 = exp1.end;
	int start2 = exp2.start;
	int end2 = exp2.end;

	addTransation(currentState, start1, "epsilon");
	addTransation(currentState, start2, "epsilon");
	addTransation(end1, currentState + 1, "epsilon");
	addTransation(end2, currentState + 1, "epsilon");

//		l.final_RES[i][j-1]=NULL;
//		l.final_RES.
//		l.final_RES[i][j-2]=NULL;

	l.final_RES[i][j].type = "operand";
	l.final_RES[i][j].start = currentState;
	l.final_RES[i][j].end = currentState + 1;
	l.final_RES[i][j].value = "derived";

	l.final_RES[i].erase(l.final_RES[i].begin() + j - 1);
	l.final_RES[i].erase(l.final_RES[i].begin() + j - 2);

	currentState += 2;
}

void ExpressionEvaluator::drawConcatenation(Expression_obj exp1,
		Expression_obj exp2, int i, int j) {
	int start1 = exp1.start;
	int end1 = exp1.end;
	int start2 = exp2.start;
	int end2 = exp2.end;

	addTransation(end1, start2, "epsilon");

//		l.final_RES[i][j-1]=NULL;
//		l.final_RES[i][j-2]=NULL;
	l.final_RES[i][j].type = "operand";
	l.final_RES[i][j].start = exp1.start;
	l.final_RES[i][j].end = exp2.end;

	l.final_RES[i].erase(l.final_RES[i].begin() + j - 1);
	l.final_RES[i].erase(l.final_RES[i].begin() + j - 2);

}

void ExpressionEvaluator::drawPlus(Expression_obj exp, int i, int j) {
	int start = exp.start;
	int end = exp.end;
	addTransation(currentState, start, "epsilon");
	addTransation(end, start, "epsilon"); //////////////////////////////////////
	addTransation(end, currentState + 1, "epsilon");
//	l.final_RES[i][j-1]=NULL;
	l.final_RES[i][j].type = "operand";
	l.final_RES[i][j].start = currentState;
	l.final_RES[i][j].end = currentState + 1;

	l.final_RES[i].erase(l.final_RES[i].begin() + j - 1);

	currentState += 2;

}
void ExpressionEvaluator::drawStar(Expression_obj exp, int i, int j) {
	int start = exp.start;
	int end = exp.end;
	addTransation(currentState, start, "epsilon");
	addTransation(end, start, "epsilon");   /////////////////////////////
	addTransation(end, currentState + 1, "epsilon");
	addTransation(currentState, currentState + 1, "epsilon");

//		l.final_RES[i][j-1]=NULL;
	l.final_RES[i][j].type = "operand";
	l.final_RES[i][j].start = currentState;
	l.final_RES[i][j].end = currentState + 1;

	l.final_RES[i].erase(l.final_RES[i].begin() + j - 1);

	currentState += 2;

}
void ExpressionEvaluator::add_rows(int number_of_rows) {
	for (int i = 0; i < number_of_rows; i++) {
		vector<Table_obj> v;
		table.push_back(v);

	}

}
