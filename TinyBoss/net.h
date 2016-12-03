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
    vector <double> inputs;//entradas
    vector <double> outputs;//salidas obtenidas
    unsigned long ni;//numero de entradas
    unsigned long no;//numero de salidas
    unsigned long nl;//numero de capas
    vector <int> nppl;//numero de perceptrones por capa
    int feedForward();
    
public:
    classNet();
    ~classNet();
    void ini(int ninput, int noutput, vector <int> numppl, double initialMu);
    void setInputs(vector <double> input);
    vector <double> getOutput();
    void fix(vector <double> errors);
};

#endif /* net_h */
