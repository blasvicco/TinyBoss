//
//  net.h
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#ifndef net_h
#define net_h

#include "layer.h"

class classNet {
private:
    vector <classLayer> Layer;//capas
    vector <float> inputs;//entradas
    vector <float> outputs;//salidas obtenidas
    unsigned long ni;//numero de entradas
    unsigned long no;//numero de salidas
    unsigned long nl;//numero de capas
    vector <int> nppl;//numero de perceptrones por capa
    int feedForward();
    
public:
    classNet();
    ~classNet();
    void ini(int ninput, int noutput, vector <int> numppl, float initialMu);
    void setInputs(vector <float> input);
    vector <float> getOutput();
    void fix(vector <float> errors);
};

#endif /* net_h */
