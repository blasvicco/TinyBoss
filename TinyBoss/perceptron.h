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

#include "activation.h"
#include "random.h"

using namespace std;

class classPerceptron {
private:
    unsigned int activationType;
    unsigned int ni;
    vector <double> ponderation;
    vector <double> input;
    double output;
    double mu = 0.6;
    double dEtotaldOutput = 0.0;
    
public:
    classPerceptron(unsigned int nip, unsigned int type, double initialMu);
    ~classPerceptron();
    void setInput(vector <double> inp);
    double getOutput();
    void setError(double error);
    vector<double> backFix(vector<double> inp);
    double feedBackware(double output, unsigned int wIndex);
    void forFix(double error, unsigned int wIndex);
    void forBiasFix(double error);
};

#endif /* perceptron_h */
