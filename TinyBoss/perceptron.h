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
    vector <float> ponderation;
    vector <float> inputs;
    float output;
    float mu = 0.6;
    float dEtotaldOutput = 0.0;
    
public:
    classPerceptron(int nip, float initialMu);
    ~classPerceptron();
    int setInputs(vector <float> input);
    float getOutput();
    void setError(float error);
    vector<float> fix(vector<float> inputs);
};

#endif /* perceptron_h */
