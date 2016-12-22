//
//  layer.h
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#ifndef layer_h
#define layer_h

#include "perceptron.h"

class classLayer {
private:
    vector <classPerceptron> Perceptron;
    vector <double> input;
    vector <double> output;
    vector <double> delta;
    unsigned int np;
    unsigned int ni;
    vector<double> feedForward(vector<double> input);
    
public:
    classLayer(unsigned int nip, unsigned int nperce, unsigned int type, double initialMu);
    ~classLayer();
    void setInput(vector <double> inp);
    vector<double> getOutput();
    void setError(vector<double> error);
    vector<double> backFix();
};

#endif /* layer_h */
