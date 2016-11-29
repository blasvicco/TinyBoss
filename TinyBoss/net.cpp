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

int classNet::feedForward() {
    vector<float> temp(inputs);
    for (int i = 0; i < nl; i++) {
        Layer[i].setInputs(temp);
        temp = Layer[i].getOutput();
    }
    outputs = temp;
    return 1;
}

void classNet::ini(int ninput, int noutput, vector<int> numppl, float initialMu) {
    classLayer *tmp;
    inputs.clear();
    outputs.clear();
    nppl.clear();
    nl = numppl.size();
    nppl = numppl;
    ni = ninput;
    no = noutput;
    Layer.clear();
    if (nl == 0) {
        tmp = new classLayer(ninput, noutput, initialMu);
        Layer.push_back(*tmp);
    } else {
        tmp = new classLayer(ninput, nppl[0], initialMu);
        Layer.push_back(*tmp);
        for (int i = 0; i < nl - 1; i++) {
            tmp = new classLayer(nppl[i], nppl[i + 1], initialMu);
            Layer.push_back(*tmp);
        }
        tmp = new classLayer(nppl[nl - 1], noutput, initialMu);
        Layer.push_back(*tmp);
    }
    nl = Layer.size();
}

void classNet::setInputs(vector<float> input) {
    inputs = input;
}

vector<float> classNet::getOutput() {
    outputs.clear();
    feedForward();
    return outputs;
}

void classNet::fix(vector <float> errors) {
    int i = 1;
    long index;
    do {
        index = nl - i;
        Layer[index].setError(errors);
        errors = Layer[index].fix();
        i++;
    } while(index > 1);
}
