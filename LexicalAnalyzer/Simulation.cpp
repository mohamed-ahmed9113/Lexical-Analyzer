/*
 * Simulation.cpp
 *
 *  Created on: 10 Apr 2013
 *      Author: Mohamed
 */

#include "Simulation.h"
#include "filewriter.h"

namespace std {

Simulation::Simulation(vector<vector<DNode> >* mfs, vector<bool>* final_state,
		vector<string>*accepte, vector<Token_obj> sym,
		vector<int> startStatesV) {
	// TODO Auto-generated constructor stub
	startStates = startStatesV;
	mfsa = mfs;
	final_states = final_state;
	accepted = accepte;
	symb = sym;
	out = "";
	first_state = startStates[0];
	simulate();
}
int Simulation::move(int state, string input) {
	for (int i = 0; i < (*mfsa)[state].size(); i++) {
		DNode o = (*mfsa)[state][i];
		if (o.input.compare(input) == 0) {
			return o.id;
		}
	}
	return -1; // can't move to state due to that input so error recovery
}
void Simulation::simulate() {
	FileReader reader("test.txt");
	string line = reader.readFile();
	int prev_next = first_state;
	int next = first_state;
	while (line == "") {
		line = reader.readFile();
	}
	while (line != "") {
		string temp = "";
		for (int i = 0; i < line.length(); i++) {
			char c = line.at(i);
			temp += c;
			string in = "";
			in += c;
			prev_next = next;
			next = move(next, in);
			// choose one start states
			if (next == -1) {
				for (int i = 1; i < startStates.size(); i++) {
					next = startStates[i];
					next = move(next, in);
					if (next != -1) {
						break;
					}
				}
			}
			if (next != -1) { //no error
				if ((*final_states)[next] == true) {
					saved_finals.push_back(temp);
					curr_states.push_back(next);
				}
			} else { //accepted or error
				if (!saved_finals.empty()) { //  take last pattern
					string found = saved_finals.at(saved_finals.size() - 1);
					//check if it is in symbol table
					if (!symb.empty()) {
						bool flag = false;
						for (int i = 0; i < symb.size(); i++) {
							Token_obj t = symb[i];
							if (found.compare(t.value) == 0) { //exist before
								out += t.name;
								out += "\n";
								flag = true;
								break;
							}
						}
						if (!flag) {
							//not found in symbol table
							string name = (*accepted)[curr_states.at(
									curr_states.size() - 1)];

							cout << name << "at index"
									<< curr_states.at(curr_states.size() - 1)
									<< endl;
							Token_obj o(name, found);
							symb.push_back(o);
							//								//erase all saved
							//								for (int k = 0; k < saved_finals.size(); k++) {
							//									saved_finals.erase(saved_finals.begin());
							//									curr_states.erase(curr_states.begin());
							//								}

							out += name;
							out += "\n";

						}
						if (c != ' ')
							i--;
						vector<string> temp1;
						vector<int> temp2;
						saved_finals = temp1;
						curr_states = temp2;
						temp = "";
						next = first_state;

					} else {
						string name = (*accepted)[curr_states.at(
								curr_states.size() - 1)];
						cout << "name" << "at index"
								<< curr_states.at(curr_states.size() - 1)
								<< endl;
						Token_obj o(name, found);
						symb.push_back(o);
						//erase all saved
						vector<string> temp1;
						vector<int> temp2;
						saved_finals = temp1;
						curr_states = temp2;
						out += name;
						out += "\n";
						temp = "";
						next = first_state;
						if (c != ' ')
							i--;
					}
				} else { //error occured-->o recovering
					if (c != ' ') {
						bool flag = false;
						// look of ot os in symbol tab
						for (int i = 0; i < symb.size(); i++) {
							Token_obj t = symb[i];
							if (in.compare(t.value) == 0) { //exist before
								out += t.name;
								out += "\n";
								flag = true;
								break;
							}
						}
						if (!flag) {
							cout << "entered in error occured at ";
							cout << c << endl;
							out += "error in : " + temp;
							out += "\n";
						}
					}
					vector<string> temp1;
					vector<int> temp2;
					saved_finals = temp1;
					curr_states = temp2;
					temp = "";
					next = first_state;

				}

			}
		}
		line = reader.readFile();
	}

	reader.~FileReader();
// write to output file
	FileWriter fr("symbol_table.txt");
	for (int i = 0; i < symb.size(); i++) {
		string t = "";
		t += "token name --> ";
		t += symb[i].name;
		t += "  | token value -->  ";
		t += symb[i].value;
		fr.writeFile(t);
	}
	fr.~FileWriter();
	FileWriter frr("out.txt");
	frr.writeFile(out);
	frr.~FileWriter();

}
Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
