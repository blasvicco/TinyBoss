//
//  perceptron.h
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#ifndef perceptron_h
#define perceptron_h

#include <vector>
#include <iostream>
#include <float.h>
#include <math.h>

using namespace std;

class classPerceptron {
private:
    int ni;
    vector <double> ponderation;
    vector <double> inputs;
    double output;
    double mu = 0.6;
    double dEtotaldOutput = 0.0;
    
public:
    classPerceptron(int nip, double initialMu);
    ~classPerceptron();
    int setInputs(vector <double> input);
    double getOutput();
    void setError(double error);
    vector<double> fix(vector<double> inputs);
};

#endif /* perceptron_h */
