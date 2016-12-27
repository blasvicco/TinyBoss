//
//  activation.cpp
//  test
//
//  Created by Blas Eugenio Vicco on 12/22/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#include "activation.h"

double Activation::f(unsigned int type, double sum) {
    switch (type) {
        case SIGMOID : {
            return 1 / (1.0 + exp(-sum));
        } break;
        default:
        case TANH: {
            return (2.0 / (1.0 + exp(-sum))) - 1.0;
        } break;
    }
}

double Activation::fprime(unsigned int type, double value) {
    switch (type) {
        case SIGMOID: {
            return value * (1.0 - value);
        } break;
        default:
        case TANH: {
            return (1.0 - pow(value, 2));
        } break;
    }
}
