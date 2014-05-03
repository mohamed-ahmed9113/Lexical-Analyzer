/*
 * File:   Lists.h
 * Author: Mohamed
 *
 * Created on April 7, 2013, 5:55 PM
 */

#ifndef LISTS_H
#define	LISTS_H
#include <list>
#include <string>
#include <stack>
#include <vector>

#include "Expression_obj.h"
#include "Token_obj.h"
using namespace std;

class Lists {
public:
    Lists();
    vector<string>RES;//list contain regular expression read from file
    vector<string>DEF; // list contain regular definitions read from file
    vector<string>punc; // list contain  punc read from file
    vector<string>keywords;// list contain keywords read from file
    vector<string> expr_names;//list contain names of regular expressions
    vector<string> def_names;//list contain names of regular definitions
    vector<Token_obj>symbol_table;//symbol table of tokens
    vector <vector <Expression_obj> > final_RES;//vector of vectors that have postfix form of expressions
    stack<char> my_stack;


    void ini_lists();
    vector<Expression_obj> to_postfix(string expr);
    bool is_symbol(char s);
    vector<Expression_obj> split(string expr);
    string trim(string s);
    void fill_symb_table(string expr,string name);
    string remove_slash(string in);
    string split_def(string in);
    string remove_unwanted_spaces(string in);
    string generate_seq(char a, char b);
    string replaceAll(string str, string from, string to);
    virtual ~Lists();
private:

};

#endif	/* LISTS_H */

