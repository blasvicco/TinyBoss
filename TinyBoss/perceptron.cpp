//
//  perceptron.cpp
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#include "perceptron.h"

classPerceptron::classPerceptron(int nip, float initialMu) {
    mu = initialMu > 0 ? initialMu : mu;
    ponderation.clear();
    inputs.clear();
    output = 0;
    ni = nip;
    float tmp;
    float signe;
    for (int i = 0; i <= ni; i++) {
        tmp = 0;
        signe = rand() % 2 == 1 ? -1.0 : 1.0;
        tmp = ((rand() % 100)/100.0) * signe;
        ponderation.push_back(tmp);
    }
}

classPerceptron::~classPerceptron() {
    //liberar memoria
}

int classPerceptron::setInputs(vector<float> input) {
    inputs.clear();
    inputs = input;
    return 1;
}

float classPerceptron::getOutput() {
    float sum = 0;
    for (int i = 0; i < ni; i++) {
        sum += inputs[i] * ponderation[i];
    }
    
    sum += ponderation[ni]; //+ via
    output = (2.0 / (1.0 + exp(-sum))) - 1.0; //sigmoide
    return output;
}

void classPerceptron::setError(float error) {
    dEtotaldOutput = error;
}

vector<float> classPerceptron::fix(vector<float> inputs) {
    float delta = dEtotaldOutput;
    vector<float> deltaBackErrors;
    for (int i = 0; i <= ni; i++) {
        deltaBackErrors.push_back(delta * ponderation[i]);
        float tmp = mu * delta * inputs[i];
        if ((ponderation[i] + tmp > -FLT_MAX) && (ponderation[i] + tmp < FLT_MAX)) {
            ponderation[i] += tmp;
        }
    }
    return deltaBackErrors;
}
