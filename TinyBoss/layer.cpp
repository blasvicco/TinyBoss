//
//  layer.cpp
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#include "layer.h"

classLayer::classLayer(unsigned int nip, unsigned int nperce, unsigned int type, double initialMu) {
    input.clear();
    output.clear();
    np = nperce;
    ni = nip;
    Perceptron.clear();
    for (unsigned int i = 0; i < np; i++) {
        classPerceptron *tmp = new classPerceptron(nip, type, initialMu);
        Perceptron.push_back(*tmp);
    }
}

classLayer::~classLayer() {
    //liberar memoria
}

void classLayer::setInput(vector<double> inp) {
    input.clear();
    input = inp;
}

vector<double> classLayer::getOutput() {
    output = feedForward(input);
    return output;
}

void classLayer::setError(vector<double> error) {
    for (unsigned int i = 0; i < np; i++) {
        Perceptron[i].setError(error[i]);
    }
}

vector<double> classLayer::backFix() {
    vector<double> deltaBackErrors;
    vector<double> deltaBackErrorsTotal(ni, 0.0);
    for (unsigned int i = 0; i < np; i++) {
        deltaBackErrors = Perceptron[i].backFix(input);
        for (unsigned int j = 0; j < ni; j++) {
            deltaBackErrorsTotal[j] += deltaBackErrors[j];
        }
    }
    return deltaBackErrorsTotal;
}

//Private
vector<double> classLayer::feedForward(vector<double> input) {
    vector<double> output;
    double tmp = 0;
    for (unsigned int i = 0; i < np; i++) {
        Perceptron[i].setInput(input);
        tmp = Perceptron[i].getOutput();
        output.push_back(tmp);
    }
    return output;
}
