/*
 * Tokenobj.h
 *
 *  Created on: 9 Apr 2013
 *      Author: Mohamed
 */

#ifndef TOKENOBJ_H_
#define TOKENOBJ_H_
#include <string>
 namespace std {

class Token_obj {
public:
	string name,value;
	Token_obj(string n,string v);
	virtual ~Token_obj();
};

} /* namespace std */
#endif /* TOKENOBJ_H_ */
