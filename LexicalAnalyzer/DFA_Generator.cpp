#include <iostream>
#include <stdlib.h>
#include <string>

#include "DFA_Generator.h"

using namespace std;

DFA_Generator::DFA_Generator(vector<vector<Table_obj*> > NFA,
		vector<string> input, vector<int> finalStates,
		vector<string> patternName, vector<string> pattern) {
	NTransitions = NFA;
	Table_obj* to = new Table_obj(0, "");
	cout << "==================================" << endl;
	printNFA(NFA);
	cout << "==================================" << endl;
	Dstates = generateDFA(input, NFA, to, finalStates, patternName, pattern);
	printDFA(Dstates);
}
DFA_Generator::~DFA_Generator() {

}

DNode* DFA_Generator::getUnmarked(vector<DNode*> states) {
	unsigned i;
	for (i = 0; i < states.size(); i++) {
		if (!states[i]->isMarked) {
			return states[i];
		}
	}
	Table_obj* temp1 = new Table_obj(-1, "");
	vector<Table_obj*> temp;
	temp.push_back(temp1);
	DNode* temp2 = new DNode(-1, "a", temp, false, false, "", "");
	return temp2;
}

vector<Table_obj*> DFA_Generator::move(vector<vector<Table_obj*> > transitions,
		string input, vector<Table_obj*> states) {
	vector<Table_obj*> to;
	unsigned i;
	unsigned k;
	unsigned l;
	for (i = 0; i < states.size(); i++) {
		int j = states[i]->state;
		for (k = 0; k < transitions[j].size(); k++) {
			if (transitions[j][k]->value.compare(input) == 0) {
				bool flag = false;
				for (l = 0; l < to.size(); l++) {
					if (to[l]->state == transitions[j][k]->state) {
						flag = true;
						break;
					}
				}
				if (!flag) {
					to.push_back(transitions[j][k]);
				}
			}
		}
	}
	return to;
}

vector<Table_obj*> DFA_Generator::epsilon_closure(vector<Table_obj*> nodes,
		vector<vector<Table_obj*> > transitions) {
	vector<Table_obj*> closure;
	stack<Table_obj*> st;
	unsigned i;
	for (i = 0; i < nodes.size(); i++) {
		st.push(nodes[i]);
		closure.push_back(nodes[i]);
	}
	while (!st.empty()) {
		Table_obj* temp = st.top();
		st.pop();
		int index = temp->state;
		for (i = 0; i < transitions[index].size(); i++) {
			Table_obj* n = transitions[index][i];
			if (n->value.compare("epsilon") == 0) {
				unsigned j;
				bool flag = false;
				for (j = 0; j < closure.size(); j++) {
					if (closure[j]->state == n->state) {
						flag = true;
						break;
					}
				}
				if (!flag) {
					closure.push_back(n);
					st.push(n);
				}
			}
		}
	}
	return closure;
}

bool DFA_Generator::contains(vector<DNode*> states, DNode* node) {
	vector<Table_obj*> v1 = node->nonDNodes;
	unsigned i;
	unsigned j;
	unsigned k;
	for (i = 0; i < states.size(); i++) {
		bool flag = false;
		vector<Table_obj*> v2 = states[i]->nonDNodes;
		if (v1.size() != v2.size())
			flag = true;
		else {
			for (j = 0; j < v2.size(); j++) {
				bool isFound = false;
				for (k = 0; k < v1.size(); k++) {
					if (v1[k]->state == v2[j]->state) {
						isFound = true;
						break;
					}
				}
				if (!isFound) {
					flag = true; //not found
					break;
				}
			}
		}
		if (!flag)
			return true;
	}
	return false;
}

DNode* DFA_Generator::check(vector<DNode*> states, vector<Table_obj*> v1) {
	unsigned i;
	unsigned j;
	unsigned k;
	for (i = 0; i < states.size(); i++) {
		bool flag = false;
		vector<Table_obj*> v2 = states[i]->nonDNodes;
		if (v1.size() != v2.size())
			flag = true;
		else {
			for (j = 0; j < v2.size(); j++) {
				bool isFound = false;
				for (k = 0; k < v1.size(); k++) {
					if (v1[k]->state == v2[j]->state) {
						isFound = true;
						break;
					}
				}
				if (!isFound) {
					flag = true; //not found
					break;
				}
			}
		}
		if (!flag)
			return states[i];
	}
	Table_obj* no = new Table_obj(-1, "");
	vector<Table_obj*> t;
	t.push_back(no);
	DNode* dno = new DNode(-1, "", t, false, false, "", "");
	return dno;
}

vector<vector<DNode*> > DFA_Generator::constructDFA(vector<string> inputs,
		vector<DNode*> states, vector<vector<Table_obj*> > transitions) {
	vector<vector<DNode*> > DTransitions;
	unsigned i;
	unsigned j;
	for (i = 0; i < states.size(); i++) {
		vector<DNode*> trans;
		for (j = 0; j < inputs.size(); j++) {
			vector<Table_obj*> temp = states[i]->nonDNodes;
			vector<Table_obj*> to = epsilon_closure(
					move(transitions, inputs[j], temp), transitions);
			DNode* target = check(states, to);
			trans.push_back(target);
		}
		DTransitions.push_back(trans);
	}
	return DTransitions;
}

vector<vector<DNode*> > DFA_Generator::generateDFA(vector<string> inputs,
		vector<vector<Table_obj*> > transitions, Table_obj* nStartState,
		vector<int> finalStates, vector<string> patternName,
		vector<string> pattern) {
	unsigned l;
	vector<vector<DNode*> > DTransitions;
	vector<DNode*> states;
	vector<Table_obj*> nStates;
	nStates.push_back(nStartState);
	DNode* dStartState = new DNode(0, "", epsilon_closure(nStates, transitions),
			false, false, "", "");
	states.push_back(dStartState);
	int count = 1;
	DNode* T = getUnmarked(states);
	unsigned i;
	int index = 0;
	//ini all isfinal vector

	for (int h = 0; h < 1000; h++) {
		isFinal.push_back(false);
		patterns.push_back("");
	}
	while (T->id != -1) {
		for (l = 0; l < T->nonDNodes.size(); l++) {
			vector<int> tempo;
			for (int k = 0; k < finalStates.size(); k++) {
				if (finalStates[k] == T->nonDNodes[l]->state) {
					isFinal[index] = true;
					tempo.push_back(k);
//					break;
				}
			}
			if (!tempo.empty()) {
				cout << finalStates.size() << " | " << patternName.size()
						<< " | " << tempo.size() << endl;
				int min = tempo[0];
				cout << min << endl;
				for (int i = 1; i < tempo.size(); i++) {
					if (tempo[i] < min) {
						min = tempo[i];
					}
					cout << min << endl;
				}
				patterns[index] = patternName[min];
			}

		}
		index++;
		cout << endl;
		T->isMarked = true;
		for (i = 0; i < inputs.size(); i++) {
			DNode* n = new DNode(-1, inputs[i],
					epsilon_closure(move(transitions, inputs[i], T->nonDNodes),
							transitions), false, false, "", "");
			bool flag;
			flag = contains(states, n);
			if (!flag) {
				n->id = count;
				states.push_back(n);
				count++;
			}
		}
		cout << "_________" << endl;
		T = getUnmarked(states);
	}
	DeterministecS = states;
//	unsigned p1;
//	unsigned p2;
//	unsigned p3;
//	for (p1 = 0; p1 < states.size(); p1++) {
//		bool fl = false;
//		for (p2 = 0; p2 < states[p1]->nonDNodes.size(); p2++) {
//			for (p3 = 0; p3 < finalStates.size(); p3++) {
//				if (finalStates[p3] == states[p1]->nonDNodes[p2]->state) {
//					fl = true;
//					states[p1]->isFinalState = true;
//					states[p1]->pattern = pattern[p3];
//					states[p1]->patternName = patternName[p3];
//					break;
//				}
//			}
//			if (fl)
//				break;
//		}
//	}
	cout
			<< ",,,,,,,,,,,,,,,,,xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx,,,,,,,,,,,,,,,,,,,,,,,"
			<< endl;
	DTransitions = constructDFA(inputs, states, transitions);
	return DTransitions;
}
void DFA_Generator::printDFA(vector<vector<DNode*> > DTransitions) {
	unsigned x;
	unsigned y;
	for (x = 0; x < DTransitions.size(); x++) {
		cout << x << " :   ";
		for (y = 0; y < DTransitions[x].size(); y++) {
			cout << DTransitions[x][y]->id << " ";
		}
		cout << endl;
	}
	cout << DTransitions.size() << endl;
}
void DFA_Generator::printNFA(vector<vector<Table_obj*> > transitions) {
	unsigned x;
	unsigned y;
	for (x = 0; x < transitions.size(); x++) {
		cout << x << " :   ";
		for (y = 0; y < transitions[x].size(); y++) {
			cout << transitions[x][y]->state << " " << transitions[x][y]->value
					<< " ";
		}
		cout << endl;
	}
}
