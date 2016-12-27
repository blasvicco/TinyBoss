//
//  net.cpp
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#include "net.h"

classNet::classNet() {
    
}

classNet::~classNet() {
    //liberar memoria
}

void classNet::ini(unsigned int ninput, unsigned int noutput, vector <unsigned int> numppl, unsigned int type, double initialMu) {
    classLayer *tmp;
    input.clear();
    output.clear();
    nppl.clear();
    nl = (unsigned int)numppl.size();
    nppl = numppl;
    ni = ninput;
    no = noutput;
    Layer.clear();
    if (nl == 0) {
        tmp = new classLayer(ninput, noutput, type, initialMu);
        Layer.push_back(*tmp);
    } else {
        tmp = new classLayer(ninput, nppl[0], type, initialMu);
        Layer.push_back(*tmp);
        for (unsigned int i = 0; i < nl - 1; i++) {
            tmp = new classLayer(nppl[i], nppl[i + 1], type, initialMu);
            Layer.push_back(*tmp);
        }
        tmp = new classLayer(nppl[nl - 1], noutput, type, initialMu);
        Layer.push_back(*tmp);
    }
    nl = (unsigned int)Layer.size();
}

void classNet::setInput(vector<double> inp) {
    input = inp;
}

vector<double> classNet::getOutput() {
    output.clear();
    feedForward(nl);
    return output;
}

void classNet::backFix(vector <double> error) {
    int index = nl - 1;
    while(index >= 0) {
        Layer[index].setError(error);
        error = Layer[index].backFix();
        index--;
    }
}

void classNet::temper(unsigned int deep, unsigned int k) {
    for (unsigned int i = 0; i < deep; i++) {
        feedForward(i+1);
        Layer[i].temper(k);
    }
}

//Private
void classNet::feedForward(unsigned int deep) {
    output = input;
    for (unsigned int i = 0; i < deep; i++) {
        Layer[i].setInput(output);
        output = Layer[i].getOutput();
    }
}
