//
//  perceptron.cpp
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#include "perceptron.h"

classPerceptron::classPerceptron(int nip, double initialMu) {
    mu = initialMu > 0 ? initialMu : mu;
    ponderation.clear();
    inputs.clear();
    output = 0;
    ni = nip;
    double tmp;
    double signe;
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

int classPerceptron::setInputs(vector<double> input) {
    inputs.clear();
    inputs = input;
    return 1;
}

double classPerceptron::getOutput() {
    double sum = 0;
    for (int i = 0; i < ni; i++) {
        sum += inputs[i] * ponderation[i];
    }
    
    sum += ponderation[ni]; //+ via
    output = (2.0 / (1.0 + exp(-sum))) - 1.0; //sigmoide
    return output;
}

void classPerceptron::setError(double error) {
    dEtotaldOutput = error;
}

vector<double> classPerceptron::fix(vector<double> inputs) {
    double delta = dEtotaldOutput;
    vector<double> deltaBackErrors;
    for (int i = 0; i <= ni; i++) {
        //cout << delta * ponderation[i]<< endl;
        deltaBackErrors.push_back(delta * ponderation[i]);
        double tmp = mu * delta * inputs[i];
        if ((ponderation[i] + tmp > -DBL_MAX) && (ponderation[i] + tmp < DBL_MAX)) {
            ponderation[i] += tmp;
        } else {
            double signe;
            signe = rand() % 2 == 1 ? -1.0 : 1.0;
            ponderation[i] = ((rand() % 100)/100.0) * signe;
        }
    }
    return deltaBackErrors;
}
