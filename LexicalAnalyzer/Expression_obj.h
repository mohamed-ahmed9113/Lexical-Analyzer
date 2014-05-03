/*
 * File:   Expression_obj.h
 * Author: Mohamed
 *
 * Created on April 8, 2013, 6:18 PM
 */

#ifndef EXPRESSION_OBJ_H
#define	EXPRESSION_OBJ_H
#include <string>
using namespace std;
class Expression_obj {
public:
    Expression_obj(string t,string v,int s,int e);
    string type,value;
    int start, end;
    bool ismarked;
    virtual ~Expression_obj();
private:

};

#endif	/* EXPRESSION_OBJ_H */

