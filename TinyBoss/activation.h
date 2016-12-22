//
//  activation.hpp
//  test
//
//  Created by Blas Eugenio Vicco on 12/22/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#ifndef activation_hpp
#define activation_hpp

#include <math.h>
const unsigned int SIGMOID = 0;
const unsigned int TANH = 1;

class Activation {
public:
    static double f(unsigned int type, double sum);
    static double fprime(unsigned int type, double value);
};

#endif /* activation_hpp */
