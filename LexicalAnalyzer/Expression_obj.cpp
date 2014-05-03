/*
 * File:   Expression_obj.cpp
 * Author: Mohamed
 *
 * Created on April 8, 2013, 6:18 PM
 */

#include "Expression_obj.h"

Expression_obj::Expression_obj(string t, string v, int s, int e){
    type=t;
    value=v;
    start=s;
    end=e;
    ismarked=false;
}

Expression_obj::~Expression_obj() {
}

