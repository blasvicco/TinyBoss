//
//  sstring.h
//  TinyBoss
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#ifndef sstring_h
#define sstring_h

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class sstring : public string {
    public:
        sstring();
        ~sstring();
        string ftos(float value);
        string itos(int value);
        string btos(bool value);
        char * stocp(string str);
};

#endif /* sstring_h */
