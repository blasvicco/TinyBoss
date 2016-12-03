//
//  moskitos.h
//  TinyBoss
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#ifndef moskitos_h
#define moskitos_h

#include "organism.h"

class Moskitos : public Organism {
private:
    classNet FlyBrain;
    classNet AvoidObstacleBrain;
    vector<double> foodDeltas;
    vector<double> foodAmount;
    vector<pos> foodPos;
    double maxDelta;
    double maxFood;
    int foodTarget;
    int memoryFoodTarget = -1;
    double winWidth;
    double winHeight;
    
    pos fly(vector<double> inputs);
    void learnToFly(vector<double> inputs);
    void chooseTarget();
    
public:
    Moskitos(double initialLife, double width, double height);
    pos move();
    void eat();
    bool reproduce();
    pos avoidObstacle(vector<double> inputs);
    void shakeAvoidObtsacleBrain();
    double rotten();
    void blink();
    void lookForFood(pos buzzP, double buzzLife);
};

#endif /* moskitos_h */
