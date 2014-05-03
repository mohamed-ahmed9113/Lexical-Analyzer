/*
 * File:   Lists.cpp
 * Author: Mohamed
 *
 * Created on April 7, 2013, 5:55 PM
 */

#include "Lists.h"
#include "filereader.h"
#include "Expression_obj.h"

Lists::Lists() {
}
/*
 * Main method that do all parsing before generating NFA and initialise all lists.
 */
void Lists::ini_lists() {
	FileReader reader("input.txt"); // object from file reader
	string line = reader.readFile();
	while (line != "") { //loop till end of file
		if (line.at(0) == '{') { //case keyword
			keywords.push_back(line);
			string l = line.substr(1, line.length() - 2);
			fill_symb_table(l, "keyword");
		} else if (line.at(0) == '[') { //case punc
			string l = line.substr(1, line.length() - 2);
			fill_symb_table(l, "punc");
			punc.push_back(line);
		} else {
			bool finish = false;
			string sub1, sub2 = "";
			// loop to find if it it is expr or def
			for (int i = 0; i < line.length(); i++) {
				if (line.at(i) == ':') { //expression
					sub1 = line.substr(i + 2, line.length());
					sub2 = line.substr(0, i - 1);
					sub1 = remove_unwanted_spaces(sub1);
					RES.push_back(sub1);
					expr_names.push_back(sub2);
					cout << line.substr(0, i).length() << endl;
					finish = true;
					break;
				} else if (line.at(i) == '=') { //definition
					sub1 = line.substr(i + 2, line.length());
					sub2 = line.substr(0, i - 1);
					sub1 = remove_unwanted_spaces(sub1);
					DEF.push_back(sub1);
					def_names.push_back(sub2);
					break;
				}
			}
		}
		line = reader.readFile();
	}

	reader.~FileReader(); // close file reader

	/*
	 * loop on all definitions and expand them and then replace the expanded form with their names in RES
	 */
	for (int i = 0; i < DEF.size(); i++) {
		string splitted = split_def(DEF[i]); //expand
		string pattern = def_names[i];
		//loop on all RES to replace that pattern with splitted ones.
		for (int j = 0; j < RES.size(); j++) {
			string l = RES[j];
			string t = replaceAll(l, pattern, splitted); //replace
			RES[j] = t;
		}

	}
	// convert each RES int its postfix
	for (int i = 0; i < RES.size(); i++) {
		string ll = RES[i];
		ll = replaceAll(ll, "\\=\\=", "= =");
		ll = replaceAll(ll, "!\\=", "! =");
		ll = replaceAll(ll, ">\\=", "> =");
		ll = replaceAll(ll, "<\\=", "< =");
//		cout<<ll<<endl;
		final_RES.push_back(to_postfix(ll));
	}
}
/*
 *Method that takes each reuglar expression and convert it to postfix form
 */
vector<Expression_obj> Lists::to_postfix(string expr) {
	string out = "";
	char open = '(';
	char close = ')';
	char astr = '*';
	char plus = '+';
	char conc = ' ';

	for (int i = 0; i < expr.length(); i++) {
		char curr = expr.at(i);
		if (!is_symbol(curr)) {
			out = out + curr;
		} else {
			if (i > 0) {
				if (expr.at(i - 1) == '\\') {
					out += curr;
					continue;
				}
			}
			if (out != "" && out.at(out.length() - 1) != '$')
				out += '$';

			if ((my_stack.empty()) || (my_stack.top() == open)
					|| (curr == open)) {
				my_stack.push(curr);
			} else {            //stack not empty
				if ((curr == astr || curr == plus)
						&& (my_stack.top() == astr || my_stack.top() == plus)) {
					out = out + my_stack.top();
					out += '$';
					my_stack.pop();
					my_stack.push(curr);
				} else if (((curr == astr) || (curr == plus))
						&& ((my_stack.top() == '|') || (my_stack.top() == conc))) {
					my_stack.push(curr);
				} else if (curr == conc && my_stack.top() == '|') {
					my_stack.push(curr);
				} else if (curr == conc
						&& ((my_stack.top() == astr) || (my_stack.top() == plus)
								|| (my_stack.top() == conc))) {
					out = out + my_stack.top();
					out += '$';
					my_stack.pop();
					if (!my_stack.empty()) {
						while ((my_stack.top() == astr)
								|| (my_stack.top() == plus)
								|| (my_stack.top() == conc)) {
							out = out + my_stack.top();
							out += '$';
							my_stack.pop();
						}
					}
					my_stack.push(curr);
				} else if (curr == '|') {
					if (!my_stack.empty()) {
						while ((!my_stack.empty()) && (my_stack.top() != open)) {
							out = out + my_stack.top();
							out += '$';
							my_stack.pop();
						}
					}
					my_stack.push(curr);
				} else if (curr == close) {
					while (my_stack.top() != open) {
						out = out + my_stack.top();
						out += '$';
						my_stack.pop();
					}
					my_stack.pop();            //pop ')'
				}

			}
		}
	}
	while (!my_stack.empty()) {
		if (out.at(out.length() - 1) != '$')
			out += '$';
		out = out + my_stack.top();
		out += '$';
		my_stack.pop();
	}
	return split(out);
}
/*
 *split RES elements by '$' and return vector of elements
 */
vector<Expression_obj> Lists::split(string expr) {
	vector<Expression_obj> t;
	bool found = false;
	int start = 0;
	string type;
	for (int i = 0; i < expr.length(); i++) {
		if (expr.at(i) == '$') {
			string value = expr.substr(start, i - start);

			if (is_symbol(value.at(0)))
				type = "operator";
			else
				type = "operand";
			Expression_obj o(type, value, -1, -1);

			t.push_back(o);
			start = i + 1;
			found = true;
		}
	}
	if (!found) {
		if (is_symbol(expr.at(0)))
			type = "operator";
		else
			type = "operand";
		Expression_obj o(type, expr, -1, -1);
		t.push_back(o);
	}
	for (int i = 0; i < t.size(); i++) {
		cout << t[i].value;
	}
	cout << endl;
	return t;
}

string Lists::remove_unwanted_spaces(string in) {
	string temp = "";
	for (int i = 0; i < in.length(); i++) {
		if (in.at(i) == ' ') {
			for (int j = i + 1; j < in.length(); j++) {
				if (in.at(j) != ' ') {
					if ((in.at(j) != '|') && (in.at(j) != ')')
							&& (in.at(j) != '+') && (in.at(j) != '-')
							&& (in.at(j) != '*')) {
						if (j >= 2) {
							if ((in.at(j - 2) != '|') && (in.at(j - 2) != '(')
									&& (in.at(j - 2) != '-')
									&& (in.at(j - 2) != ' '))
								temp += ' ';
						}
					}
					i = j - 1;
					break;
				}
			}
		} else {
			temp += in.at(i);
		}
	}
	string temp2 = "";
	for (int i = 0; i < temp.length(); i++) {
		if (temp.at(i) == '(') {
			if (i > 0) {
				if (temp.at(i - 1) != ' ') {
					if (i > 1) {
						if (temp.at(i - 2) != '|') {
							temp2 += ' ';
						}
					}
				}
			}
		}
		temp2 += temp.at(i);
	}
	return temp2;
}

/*
 * Method that check if the input char is symbol
 */
bool Lists::is_symbol(char s) {
	if ((s == ')') || (s == '(') || (s == '*') || (s == '+') || (s == ' ')
			|| (s == '|')) {
		return true;
	}
	return false;
}
/*
 * method that take keywords or punctuation line and then insert them in symbol table
 */
void Lists::fill_symb_table(string expr, string name) {
	int start = 0;
	string exprr = trim(expr);
	for (int i = 0; i < exprr.length(); i++) {
		if (exprr.at(i) == ' ') {
			string value = exprr.substr(start, i - start);
			value = remove_slash(value);
			Token_obj o(name, value);
			symbol_table.push_back(o);
			start = i + 1;

		}
	}
}
/*
 * Method that remove spaces form end and beginning of the param string
 */
string Lists::trim(string s) {
	string temp;
	//loop to remove from beginning
	for (int i = 0; i < s.length(); i++) {
		if (s.at(i) != ' ') {
			temp = s.substr(i);
			break;
		}
	}
	//loop to remove from end
	for (int i = temp.length() - 1; i >= 0; i--) {
		if (temp.at(i) != ' ') {
			temp = temp.substr(0, i + 1);
			break;
		}

	}
	temp += ' ';

	return temp;

}
/*
 * Method that remove back slash from any reserved symbol
 */
string Lists::remove_slash(string in) {
	string temp = "";
	if (in.length() > 1) {
		for (int i = 0; i < in.length(); i++) {
			if (in.at(i) != '\\')
				temp += in.at(i);
		}
	} else
		temp = in;
	return temp;
}
/*
 * Method that generate expanded form of regular definitions
 */
string Lists::split_def(string in) {
	string temp = "";
	for (int i = 0; i < in.length(); i++) {
		if (in.at(i) == '-') {
			char before = in.at(i - 1);
			char after = in.at(i + 1);
			i++;
			temp = temp.substr(0, temp.length() - 1);
			temp += generate_seq(before, after);

		} else
			temp += in.at(i);
	}
	return temp;
}
/**
 * Method that take char before '-' and char after then expand expression of OR's
 */
string Lists::generate_seq(char a, char b) {
	int x = a;
	int y = b;
	string temp = "(";
	for (int i = x; i <= y; i++) {
		temp += (char) i;
		temp += '|';
	}
	temp = temp.substr(0, temp.length() - 1);
	temp += ')';
	return temp;
}
/**
 * Method that take string and replace a string with occurrence of the other.
 */
string Lists::replaceAll(string str, string from, string to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
	return str;
}

Lists::~Lists() {
}

