/*
 * DFAGenerator.h
 *
 *  Created on: 10 Apr 2013
 *      Author: Mohamed
 */

#ifndef DFAGENERATOR_H_
#define DFAGENERATOR_H_
#include "DNode.h"
#include <vector>
#include <stack>
#include "Table_obj.h"
#include  <string>

namespace std {

class DFA_Generator {
public:
	vector<vector<Table_obj*> > NTransitions;
	DFA_Generator(vector<vector<Table_obj*> > NFA, vector<string> input,
			vector<int> finalStates, vector<string> patternName,
			vector<string> pattern);
	DNode* getUnmarked(vector<DNode*> states);
	vector<Table_obj*> move(vector<vector<Table_obj*> > transitions,
			string input, vector<Table_obj*> states);
	vector<Table_obj*> epsilon_closure(vector<Table_obj*> nodes,
			vector<vector<Table_obj*> > transitions);
	bool contains(vector<DNode*> states, DNode* node);
	DNode* check(vector<DNode*> states, vector<Table_obj*> v1);
	vector<vector<DNode*> > constructDFA(vector<string> inputs,
			vector<DNode*> states, vector<vector<Table_obj*> > transitions);
	vector<vector<DNode*> > generateDFA(vector<string> inputs,
			vector<vector<Table_obj*> > transitions, Table_obj* nStartState,
			vector<int> finalStates, vector<string> patternName,
			vector<string> pattern);
	void printDFA(vector<vector<DNode*> > DTransitions);
	void printNFA(vector<vector<Table_obj*> > transitions);
	void AccStates(vector<DNode*> states);
	vector <bool>isFinal;
	vector <string> patterns;
	vector<vector<DNode *> > Dstates;
	vector<DNode*> DeterministecS;
	virtual ~DFA_Generator();
};

} /* namespace std */
#endif /* DFAGENERATOR_H_ */
