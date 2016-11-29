//
//  sstring.cpp
//  TinyBoss
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#include "sstring.h"

sstring::sstring() : string() {

}

sstring::~sstring() {
    
}

string sstring::ftos(float value) {
    ostringstream ostr;
    ostr << setprecision(3) << value;
    string s(ostr.str());
    return s;
}

string sstring::itos(int value) {
    ostringstream ostr;
    ostr << value;
    string s(ostr.str());
    return s;
}

string sstring::btos(bool value) {
    if (value) {
        return "true";
    } else {
        return "false";
    }
}

char * sstring::stocp(string str) {
    char * ptrTarget = NULL;
    
    ptrTarget = new char[str.size() + 1];
    return ptrTarget;
}
