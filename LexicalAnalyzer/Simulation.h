/*
 * Simulation.h
 *
 *  Created on: 10 Apr 2013
 *      Author: Mohamed
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_
#include "FileReader.h"
#include "Table_obj.h"
#include <vector>
#include "Token_obj.h"
#include "DNode.h"
namespace std {

class Simulation {
public:
	void simulate();
	int move(int state, string input);
	vector<string> saved_finals;
	vector<int> curr_states;
	vector<vector<DNode> >* mfsa;
	vector<bool>* final_states;
	vector<string>*accepted;
	vector<Token_obj> symb;
	vector<int> startStates;
	string out;
	int first_state;
	Simulation(vector<vector<DNode> >* mfs, vector<bool>* final_state,
			vector<string>*accepte, vector<Token_obj> sym,
			vector<int>  startStatesV);

	virtual ~Simulation();
};

} /* namespace std */
#endif /* SIMULATION_H_ */
