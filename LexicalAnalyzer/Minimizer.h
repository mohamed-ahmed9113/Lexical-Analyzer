/*
 * Minimizer.h
 *
 *  Created on: Apr 9, 2013
 *      Author: azmy
 *      this class minimizes a Deterministic Finite State Machine
 *      using equivalent classes technique
 */
#include"DisJointNode.h"
#include"DisjoinList.h"
#include<vector>
#include <stack>
#include<string>
#include <iostream>
#include <sstream>
#ifndef MINIMIZER_H_
#define MINIMIZER_H_
#define DUMMY -60696 // to identify dummy nodes in disjoint lists
using namespace std;

class Minimizer {
public:
	void printMinStack();
	vector<vector<DNode> > *minResult;
	vector<bool>*isfinalMin;
	vector <int> startMinstates;
	vector<string>*minPatterns;
	vector<int>*patternsPriority;
	//int DUMMY = -60696;
	int setNum;

	vector<bool> *isStart;
	int inputNum;
	int *dummy;
	Minimizer(vector<vector<DNode*> > *dfa, vector<bool>*isFinalVector,
			vector<string> *pattern, vector<string> *input_names, int numStates,
			int numInputs, vector<DNode*> DeterministecS);
	void minimize();

	virtual ~Minimizer();
private:
	vector<int> startStates;
	int listid;
	int findIndex(string namem, vector<string> *vnames);
	vector<string> *patterns;
	vector<vector<DNode*> > *dfa; //the DFA passed to the class
	vector<bool> *isFinalVector;
	vector<DisJointNode<int> *> *dsetsVector;
	list<DisjoinList<int>*> *statesStack;
	list<vector<DisJointNode<int> *> *>*statesDsetsStack;
	list<DisjoinList<int>*>*minmizedStatesStack;
	DisjoinList<int> *nonfinal;
	vector<string> *input_names;
};
#endif /* MINIMIZER_H_ */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Initialize the final and non final lists and put them in the stack to start
 * the minimization algorithm
 * Remember:
 * after creation of new lists in the minimization algorithm
 * update the dsetsvector
 */
Minimizer::Minimizer(vector<vector<DNode*> > *dfa, vector<bool>*isFinalVector,
		vector<string> *pattern, vector<string> *input_names, int numStates,
		int numInputs, vector<DNode*> DeterministecS) {
//	for (int i = 0; i < dfa->size(); i++) {
//		for (int j = 0; j < (*dfa)[i].size(); j++) {
//			cout << (*dfa)[i][j]->input << " trans: " << (*dfa)[i][j]->id
//					<< "       ";
//		}
//		cout << "" << endl;
//	}

	setNum = numStates;
	inputNum = numInputs;
	this->input_names = input_names;
	minResult = new vector<vector<DNode> >();
	isfinalMin = new vector<bool>();
	minPatterns = new vector<string>();
	patternsPriority = new vector<int>();
	this->minmizedStatesStack = new list<DisjoinList<int>*>();
	listid = 0;
	dummy = new int();
	*dummy = -1;
	this->statesDsetsStack = new list<vector<DisJointNode<int> *> *>();
	this->patterns = pattern;
	this->statesStack = new list<DisjoinList<int>*>();
	this->dfa = dfa;
	this->isFinalVector = isFinalVector;
	this->dsetsVector = new vector<DisJointNode<int> *>();
	DisJointNode<int> *nfDummy = new DisJointNode<int>(*dummy); // dummy node for the non final list
	this->nonfinal = new DisjoinList<int>(nfDummy);
	stringstream ss;
	ss << listid;
	string sName = "s" + ss.str();
	nonfinal->root->setName = sName;
	++listid;
	vector<DisjoinList<int> *> *finals = new vector<DisjoinList<int> *>(); //remember to deallocate
	vector<string> *finalsPatterns = new vector<string>(); //remember to deallocate

	//cout<<"iterating on patterns vector"<<endl;
	for (int i = 0; i < patterns->size(); ++i) {
		cout << "----------------------------------" << i << endl;
		string currentPattern = (*patterns)[i];
		cout << "iteration: " << i << " currentpattern= " << currentPattern
				<< endl;
		DisJointNode<int>*tempRoot = new DisJointNode<int>(i);
		DisjoinList<int> *currList = new DisjoinList<int>(tempRoot);

		stringstream ss;
		ss << listid;
		string sName = "s" + ss.str();
		currList->root->setName = sName;
		++listid;

		cout << "list name : " << currList->root->setName << " row : "
				<< (currList->root->coreNode) << endl;

		dsetsVector->push_back(currList->root); //add the disjoint node pointer to the dsetsVector, does root in destvector change after union??!!
		if (currentPattern.compare("") == 0) //ns2l H
				{
			cout << "the current state is NON-final" << endl;
			//non final state
			//Union with non final list
			nonfinal->unionSets(currList);

			/****
			 *
			 *
			 *
			 */
			list<DisJointNode<int>*> nfn;
			nonfinal->getList(&nfn);
			list<DisJointNode<int>*>::iterator it = nfn.begin();

			for (int t = 0; it != nfn.end(); ++it) {
				cout << "node name " << (*it)->setName << "  row "
						<< ((*it)->coreNode) << endl;

			}

			/**
			 *
			 *
			 *
			 */

			cout << "list " << currList << "is unioned to nonfinal states"
					<< endl;
			cout << "current list name " << currList->root->setName << endl;
		} else {
			cout << "---------------the current state is final----------------"
					<< endl;
			bool isFound = false;
			for (int j = 0; j < finalsPatterns->size(); j++) {
				string osama = (*finalsPatterns)[j];
				cout << "checking final patterns list current final pattern = "
						<< osama << endl;
				if (osama.compare("") == 0)
					continue;
				if (osama.compare(currentPattern) == 0) {
					DisjoinList<int> *currFinal = (*finals)[j];
					if (currFinal == NULL) //finals is intially empty
					{
						cout << "currfinal--null" << endl;
//						finals->push_back(currList);
//						cout<<"list "<<currList<<"is pushed to final states"<<endl;
//						isFound = true;
//						break;
					}
					//collision tookplace
					(*finals)[j]->unionSets(currList);
					cout << "list " << currList << "is unioned to final states"
							<< endl;
					isFound = true;
					break;
				}
			}
			if (!isFound) {
				cout << "no collision detected push new list" << endl;
				finals->push_back(currList);
				finalsPatterns->push_back(currentPattern);
				cout << "no collision detected push new patern "
						<< currentPattern << endl;
			}
		}
	}

	cout << "pushing disjoint sets to the sets stack" << endl;

	for (int k = 0; k < finals->size(); k++) {
		statesStack->push_front((*finals)[k]);
		cout << "push final:  " << (*finals)[k]->root->setName << endl;
		statesDsetsStack->push_front(dsetsVector);
	}
	statesStack->push_front(nonfinal); //push non final states to the stack
	cout << "push non final  " << nonfinal->root->setName << endl;
	statesDsetsStack->push_front(dsetsVector);

	cout << "||| FROM HERE STACK IS INTIALIZED |||" << endl;

	unsigned t1;
	unsigned t2;
	for (t1 = 0; t1 < DeterministecS.size(); t1++) {
		for (t2 = 0; t2 < DeterministecS[t1]->nonDNodes.size(); t2++) {
			if (DeterministecS[t1]->nonDNodes[t2]->state == 0) {
				startStates.push_back(DeterministecS[t1]->id);
				cout<<DeterministecS[t1]->id<<" <<<<<<<<"<<endl;
			}
		}
	}
	cout<<"+++++++++++"<<endl;
	for (unsigned kkk = 0; kkk < DeterministecS.size(); kkk++) {
		cout << DeterministecS[kkk]->id << " " << DeterministecS[kkk]->input
				<< " " << DeterministecS[kkk]->isFinalState << " "
				<< DeterministecS[kkk]->pattern << " " << endl;
	}
	cout<<"+++++++++++"<<endl;
	minimize();

}

void Minimizer::minimize() {
	//first convert the adjacency list into a 2D array
	//rows=inputs
	//clos=states
	//when no trans between state and input put input[row][col]=DUMMY;

	minResult = new vector<vector<DNode> >(minmizedStatesStack->size());
	int input[setNum][inputNum];
	for (int i = 0; i < setNum; i++) {
		for (int j = 0; j < inputNum; j++) {
			input[i][j] = *dummy;
		}
	}
	for (int i = 0; i < dfa->size(); i++) {
		for (int j = 0; j < (*dfa)[i].size(); j++) {
			int col = findIndex((*dfa)[i][j]->input, input_names);
			//cout<<(*dfa)[i][j]->input<<endl;
			input[i][col] = (*dfa)[i][j]->id;
		}
		//cout<<""<<endl;
	}

	for (int i = 0; i < setNum; i++) {
		for (int j = 0; j < inputNum; j++) {
			cout << input[i][j] << "  ";
		}
		cout << "" << endl;
	}

	//the stack loop
	//make two iterartors one for the states stack
	//the other for the statesstackdsets

	list<DisjoinList<int>*>::iterator statesStackIt = statesStack->begin();
	list<vector<DisJointNode<int> *> *>::iterator statesStackDsetsIt =
			statesDsetsStack->begin();
	while (statesStackIt != statesStack->end()) {
		cout << "|||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		DisjoinList<int> *currentList = *statesStackIt; // set poped of stack (see not pop)
		cout << "poped list of the sets stack = " << currentList->root->setName
				<< endl;
		vector<DisJointNode<int> *> *currentDsetsVector = *statesStackDsetsIt; //set's dsetvector (see not pop)
		vector<DisJointNode<int> *> *newDsetVector = new vector<
				DisJointNode<int> *>(setNum); //the new dsetvector
		vector<string> transtions; //vector of string transitions
		vector<DisjoinList<int> *> newLists; //vector of new sets created
		list<DisJointNode<int>*> *listNodes = new list<DisJointNode<int>*>(); //list holding popped set's nodes for iteration purpose
		currentList->getList(listNodes);
		list<DisJointNode<int>*>::iterator nodesIt = listNodes->begin();
		/**
		 * loop on the popped set nodes
		 * for each node create a list, here you have two options
		 * 1-union it with a list with the same string of trans
		 * 2-no union, add the set to the newlists vector amd add the trans string to the transitions vectro (same index)
		 */
		cout << "loooping on the poped set nodes " << endl;
		for (int i = 0; nodesIt != listNodes->end(); ++nodesIt) {
			DisJointNode<int> *currNode = *nodesIt;
			int row = (currNode->coreNode); // currNode->coreNode is an int pointer, get its value
			cout << "current fetched Row = " << row << endl;
			if (row == *dummy) {
				cout << "dummy node found" << endl;
				continue;
			}
			DisJointNode<int>*tempRoot = new DisJointNode<int>(row);
			DisjoinList<int> *currList = new DisjoinList<int>(tempRoot);
			stringstream ss;
			ss << listid;
			currList->root->setName = "s" + ss.str();
			++listid;
			(*newDsetVector)[row] = currList->root;
			string trans; //the transition string
			for (int m = 0; m < inputNum; ++m) {
				if (input[row][m] == *dummy) {
					trans += "-";
				} else {
					//TODO zbt el 2samy
					trans += currList->find(
							(*currentDsetsVector)[input[row][m]])->setName;
				}
			}
			cout << "transitions on current node is = ->>>>" << trans << endl;
			cout
					<< "||||||||||||||||||checking if trans makes collision|||||||||||||||||||||| "
					<< endl;
			bool isFound = false;
			for (int j = 0; j < transtions.size(); ++j) {
				cout << "current trans in transitions vector is "
						<< transtions[j] << endl;
				string transCurr = transtions[j];
				if (transCurr.compare(trans) == 0) {
					cout << "collision detected" << endl;
					cout << "unioning " << currList->root->setName << " and "
							<< newLists[j]->root->setName << endl;
					currList->unionSets(newLists[j]);
					isFound = true;
					break;
				}

			}
			if (!isFound) {
				cout << "no collision detected" << endl;
				cout << "pushing " << currList->root->setName << endl;
				newLists.push_back(currList);
				transtions.push_back(trans);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////
		statesStack->pop_front(); //does this mess up the iterator !!!!!!!!!!!!!!!!!!!!!! yes
		statesDsetsStack->pop_front();
		///////////////////////////////////////////////////////////////

		//filling the new dsets vector gaps
		cout << "filling the new dsets vector gaps" << endl;
		for (int y = 0; y < newDsetVector->size(); ++y) {
			if ((*newDsetVector)[y] == NULL) {
				//cout << "gap " << y << " is filled" << endl;
				(*newDsetVector)[y] = (*currentDsetsVector)[y];
			}
		}

//		cout << "printing the currentdset vector" << endl;
//				for (int ro = 0; ro < currentDsetsVector->size(); ++ro) {
//					cout << currentList->find((*currentDsetsVector)[ro])->setName << endl;
//
//				}
//				cout<<"///////////////////////////"<<endl;
//		cout << "printing the newdsets vector" << endl;
//		for (int ro = 0; ro < newDsetVector->size(); ++ro) {
//			cout << currentList->find((*newDsetVector)[ro])->setName << endl;
//
//		}

		if (newLists.size() == 1) {
			cout << "adding to minimized stack  " << currentList->root->setName
					<< endl;
			minmizedStatesStack->push_front(currentList); //minimized list is found
			//re intialize the iterators
			statesStackIt = statesStack->begin();
			statesStackDsetsIt = statesDsetsStack->begin();
			//check if you are in the last iteration
			//we need to set the dsetsVector with the new vector to be able to use find()
			if (statesDsetsStack->size() == 0) {
				cout << "++++++++++++++++++++++++++++++++++++++++++++++"
						<< endl;
				this->dsetsVector = newDsetVector;
//				cout << "printing the dsetsvector" << endl;
//				for (int ro = 0; ro < dsetsVector->size(); ++ro) {
//					cout << currentList->find((*dsetsVector)[ro])->setName
//							<< endl;
//
//				}
			}
			/////////////////////////////////////
			continue;
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		cout << "updating the sets stack" << endl;
		for (int k = 0; k < newLists.size(); k++) {
			cout << "pushing " << newLists[k]->root->setName << "in statesStack"
					<< endl;
			statesStack->push_front(newLists[k]); //push specialized sets to the sert stack
			statesDsetsStack->push_front(newDsetVector); //associate DsetsVector
		}

		//re intialize the iterators
		statesStackIt = statesStack->begin();
		statesStackDsetsIt = statesDsetsStack->begin();
		/////////////////////////////////////

//		++statesStackDsetsIt;
	}

	cout
			<< "-----------------------------RESULT---------------------------------------------"
			<< endl;

	//Initializing  the min-result vectors
	this->isStart = new vector<bool>(minmizedStatesStack->size());
	for (int vs = 0; vs < isStart->size(); ++vs) {
		(*isStart)[vs] = false;
	}

	minResult = new vector<vector<DNode> >(minmizedStatesStack->size());
	isfinalMin = new vector<bool>(minmizedStatesStack->size());
	minPatterns = new vector<string>(minmizedStatesStack->size());
	patternsPriority = new vector<int>(minmizedStatesStack->size());
	for (int y = 0; y < minmizedStatesStack->size(); ++y) {
		vector<DNode> v; //= ew vector<Node>();//
		(*minResult)[y] = v;
	}
	vector<string>*nodesNames = new vector<string>(minmizedStatesStack->size());
	list<DisjoinList<int>*>::iterator it = minmizedStatesStack->begin();
	for (int fo = 0; it != minmizedStatesStack->end(); ++it) {
		string listName = (*it)->root->setName;
		(*nodesNames)[fo] = listName;
		int rootStateIndex = (*it)->root->coreNode;
		cout << "list name: " << listName << " root index: " << rootStateIndex
				<< endl;
		++fo;
	}
	//print sets names
	cout << "print sets names" << endl;
	for (int u = 0; u < nodesNames->size(); ++u) {
		cout << (*nodesNames)[u] << endl;
	}

///////////////////////////////////////////////////////////////////////////////////////

	list<DisjoinList<int>*>::iterator it3 = minmizedStatesStack->begin();
	for (int fe = 0; it3 != minmizedStatesStack->end(); ++it3) {

		list<DisJointNode<int>*> nfn;
		(*it3)->getList(&nfn);
		list<DisJointNode<int>*>::iterator nodesIt = nfn.begin();
		for (int t = 0; nodesIt != nfn.end(); ++nodesIt) {

			/**
			 * here you have the nodes
			 */

			bool currentNodeState = (*isFinalVector)[(*nodesIt)->coreNode];
			if (currentNodeState) {
				int minindex = findIndex((*it3)->find((*nodesIt))->setName,
						nodesNames);
				//int minindex=findIndex((*it3)->root->setName,nodesNames);
				(*isfinalMin)[minindex] = true;
				int prevPatternPriority = (*patternsPriority)[minindex];
				if (prevPatternPriority == NULL) {
					(*minPatterns)[minindex] =
							(*patterns)[(*nodesIt)->coreNode];
//					(*patternsPriority)[(*nodesIt)->coreNode] =
//							(*nodesIt)->coreNode;
					(*patternsPriority)[minindex] = (*nodesIt)->coreNode;

				} else if (prevPatternPriority >= (*nodesIt)->coreNode) {
					(*minPatterns)[minindex] =
							(*patterns)[(*nodesIt)->coreNode];
					(*patternsPriority)[minindex] = (*nodesIt)->coreNode;
//					(*this->patternsPriority)[(*nodesIt)->coreNode] =
//							(*nodesIt)->coreNode;
				}
			} else {

			}

		}

		DisJointNode<int> *root = (*it3)->root;
		int rootIndex = root->coreNode;
		int minmizedIndex = findIndex(root->setName, nodesNames); //add node in this row

		for (int g = 0; g < inputNum; ++g) {
			string transInputName = (*input_names)[g];
			int transitionStateId = input[rootIndex][g];
			/*****
			 * get the seeet name
			 */
			list<DisjoinList<int>*>::iterator temp = it3;
			list<DisjoinList<int>*>::iterator nested =
					minmizedStatesStack->begin();
			int mintransitionStateId = -1;
			for (int fg = 0; nested != minmizedStatesStack->end(); ++nested) {
				list<DisJointNode<int>*> nfn1;
				(*nested)->getList(&nfn1);
				list<DisJointNode<int>*>::iterator ooman = nfn1.begin();
				for (int h = 0; ooman != nfn1.end(); ++ooman) {
					int statenum = (*ooman)->coreNode;
					//check if index belongs to startstates indexes
					for (int is=0; is < startStates.size(); ++is) {
						int currindex = startStates[is];
						if (statenum == currindex) {
							(*isStart)[fg] = true;
						}

					}
					if (statenum == transitionStateId) {
						mintransitionStateId = fg;
						break;
					}

				}
				++fg;

			}

//			int mintransitionStateId = findIndex(
//					(*it3)->find((*dsetsVector)[transitionStateId])->setName,
//					nodesNames); //will be inserted in the new node
			//create node and add it
			DNode newNode;
			newNode.id = mintransitionStateId;
			newNode.input = transInputName;
//			DNode newnode(transInputName, mintransitionStateId);
			(*minResult)[minmizedIndex].push_back(newNode);
		}

	}
	cout << "------------end this phase--------------------" << endl;
//////////////////////////////////////////////////////////////testing ///////////////////////
	int input1[minmizedStatesStack->size()][inputNum];
	for (int i = 0; i < minmizedStatesStack->size(); i++) {
		for (int j = 0; j < inputNum; j++) {
			input1[i][j] = *dummy;
		}
	}
	for (int i = 0; i < minmizedStatesStack->size(); i++) {
		for (int j = 0; j < (*minResult)[i].size(); j++) {
			int col = findIndex((*minResult)[i][j].input, input_names);
			input1[i][col] = (*minResult)[i][j].id;
		}
	}

	for (int i = 0; i < minmizedStatesStack->size(); i++) {
		for (int j = 0; j < inputNum; j++) {
			if (input1[i][j] == -1) {
				cout << "" << input1[i][j] << "  ";
			} else {
				cout << " " << input1[i][j] << "  ";

			}
		}
		cout << "is final : " << (*isfinalMin)[i] << "   pattern is  "
				<< (*minPatterns)[i] << endl;

	}

//	cout << "start states are " << minStartStateIndex << endl;
	for (int ssi = 0; ssi < isStart->size(); ++ssi) {
		if ((*isStart)[ssi]==true)
		{
			cout <<"index is   "<< ssi << endl;
			startMinstates.push_back(ssi);
		}

	}
//	//print finals vector

}
int Minimizer::findIndex(string namem, vector<string> *vnames) {
	for (int i = 0; i < vnames->size(); ++i) {
		if ((*vnames)[i].compare(namem) == 0) {
			return i;
		}

	}
	return -1;
}
void Minimizer::printMinStack() {
}
Minimizer::~Minimizer() {

}

