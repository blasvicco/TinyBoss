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
    vector <float> inputs;
    vector <float> outputs;
    vector <float> delta;
    int np;
    int ni;
    
public:
    classLayer(int nip, int npercep, float initialMu);
    ~classLayer();
    void setInputs(vector <float> input);
    vector<float> getOutput();
    void setError(vector<float> error);
    vector<float> fix();
};

#endif /* layer_h */
