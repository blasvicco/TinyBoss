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
    vector <double> inputs;
    vector <double> outputs;
    vector <double> delta;
    int np;
    int ni;
    
public:
    classLayer(int nip, int npercep, double initialMu);
    ~classLayer();
    void setInputs(vector <double> input);
    vector<double> getOutput();
    void setError(vector<double> error);
    vector<double> fix();
};

#endif /* layer_h */
