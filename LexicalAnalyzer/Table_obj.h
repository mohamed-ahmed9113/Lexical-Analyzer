/*
 * File:   Table_obj.h
 * Author: Mohamed
 *
 * Created on April 8, 2013, 7:24 PM
 */

#ifndef TABLE_OBJ_H
#define	TABLE_OBJ_H
#include <string>
using namespace std;

class Table_obj {
public:
    Table_obj(int s,string v);
    virtual ~Table_obj();
    int state;
    string value;
private:

};

#endif	/* TABLE_OBJ_H */

