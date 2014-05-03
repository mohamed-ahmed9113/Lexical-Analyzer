/*
 * File:   main.cpp
 * Author: Mohamed
 *
 * Created on April 7, 2013, 5:39 PM
 */

#include <cstdlib>
#include "lists.h"
#include <iostream>
#include <vector>
#include <string>
#include "ExpressionEvaluator.h"
#include "DFA_Generator.h"
#include "Minimizer.h"
#include  "Simulation.h"
#include "DNode.h"
using namespace std;

/*
 *
 */

int main() {

	ExpressionEvaluator e;
	vector<vector<DNode*> > states;
	Table_obj* to = new Table_obj(0, "");
	DFA_Generator d(e.NFA, e.inputs, e.finalStates, e.l.expr_names, e.l.RES);
	states = d.Dstates;
	vector<string> temp(states.size());
//	cout<<"-------------------patterns---------------"<<endl;
	for (int i = 0; i < states.size(); i++) {
		temp[i]=d.patterns[i];
		//cout<<"index "<<i<<temp[i]<<endl;
	}
	//cout<<"-------------------------------------------"<<endl;
	vector<bool> isfinal(states.size());
	for (int i = 0; i < states.size(); i++) {
	//	cout<<"index "<<i<<"------------------is final-----------------";
		isfinal[i]=d.isFinal[i];
//		cout<<d.isFinal[i]<<endl;
	}
//	cout
//	<< "---------------------------------------------------------------------"
//			<< endl;
//	for (unsigned p = 0; p < states.size(); p++) {
//		for (unsigned q = 0; q < states[p].size(); q++) {
//			if (states[p][q]->isFinalState) {
//				isfinal[states[p][q]->id] = true;
//			} else
//				isfinal[states[p][q]->id] = false;
//		}
//	}
//
//	for (unsigned p = 0; p < d.isFinal.size(); p++) {
//		if (d.isFinal[p] == true) {
//			cout << "index at : ";
//			cout << p;
//			cout << endl;
//		}
//	}
//	cout << "????????????????????????" << endl;
//	for (int i = 0; i < e.finalStates.size(); i++) {
//		cout << e.finalStates[i] << endl;
//	}
	//cout << "????????????????????????????" << endl;
//
//	for (int i = 0; i < isfinal.size(); i++) {
//		if (isfinal[i] == true) {
//			cout << "index  ";
//			cout << i;
//			cout<<endl;
//		}
//	}
	//cout << "????????????????????????????" << endl;
	//
//
//	for (int i = 0; i < e.inputs.size(); i++) {
//		cout << e.inputs[i] << endl;
//	}
//	vector<string> patterns(states.size());
//	//patterns = e.l.RES;

//	for (int i = 0; i < e.table.size(); i++) {
//		for (int j = 0; j < e.table[i].size(); j++) {
//			cout << "index  :";
//			cout << i;
//			cout << "   state :  ";
//			cout << e.table[i][j].state;
//			cout << "   vlalue:   ";
//			cout << e.table[i][j].value << endl;
//		}
//		cout << "----------------------" << endl;
//	}
//	cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << endl;
//	for (int i = 0; i < temp.size(); i++) {
//
//		cout << d.patterns[i] << endl;
//
//	}
//	cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << endl;
//	///////////////////////////////////
////	isfinal[1] = true;
//	patterns[1] = e.l.RES[0];
////	isfinal[3] = true;
//	patterns[3] = e.l.RES[0];
////	isfinal[4] = true;
//	patterns[4] = e.l.RES[0];
/////////////////////////////////
	Minimizer min(&states, &isfinal, &temp, &e.inputs, states.size(),
			e.inputs.size(),d.DeterministecS);
//	for(int i=0;i<min.minPatterns->size();i++){
		//cout<<"pattern at "<<i <<" "<<(*min.minPatterns)[i];
		//cout<<"   "<<(*min.isfinalMin)[i]<<endl;
	//}
//	cout<<":("<<endl;
	Simulation s(min.minResult, min.isfinalMin, min.minPatterns,
			e.l.symbol_table, min.startMinstates);
	//cout<<s.out<<endl;
//
//	for(int i=0;i<e.inputs.size();i++){
//		cout<<e.inputs[i];
//		cout<<" ";
//	}
//	cout<<endl;
}

//int main23(int argc, char** argv) {
//
//	ExpressionEvaluator e;
////	DFA_Generator d(e.NFA, e.inputs, e.finalStates, e.l.expr_names, e.l.RES);
//
//	for (int i = 0; i < e.table.size(); i++) {
//		for (int j = 0; j < e.table[i].size(); j++) {
//			cout << "index  :";
//			cout << i;
//			cout << "   state :  ";
//			cout << e.table[i][j].state;
//			cout << "   vlalue:   ";
//			cout << e.table[i][j].value << endl;
//		}
//		cout << "----------------------" << endl;
//	}
//
////    for(int i=0;i<e.l.symbol_table.size();i++){
////    	cout <<"name : ";
////    	cout<<e.l.symbol_table[i].name;
////    	cout<<"  value:  ";
////    	cout<<e.l.symbol_table[i].value<<endl;
////    }
//	cout << "--------------------------" << endl;
//	for (int i = 0; i < e.inputs.size(); i++) {
//		cout << e.inputs[i] + "  ";
//	}
//	cout << endl;
//	return 0;
//}

