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
    vector<float> foodDeltas;
    vector<float> foodAmount;
    vector<pos> foodPos;
    float maxDelta;
    float maxFood;
    int foodTarget;
    int memoryFoodTarget = -1;
    float winWidth;
    float winHeight;
    
    pos fly(vector<float> inputs);
    void learnToFly(vector<float> inputs);
    void chooseTarget();
    
public:
    Moskitos(float initialLife, float width, float height);
    pos move();
    void eat();
    bool reproduce();
    pos avoidObstacle(vector<float> inputs);
    void shakeAvoidObtsacleBrain();
    float rotten();
    void blink();
    void lookForFood(pos buzzP, float buzzLife);
};

#endif /* moskitos_h */
