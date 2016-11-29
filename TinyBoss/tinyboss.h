//
//  boss.h
//  TinyBoss
//
//  Created by Blas Eugenio Vicco on 11/26/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#ifndef tinyboss_h
#define tinyboss_h

#include "organism.h"

class TinyBoss : public Organism {
private:
    classNet FearBrain;
    classNet FoodBrain;
    float size;
    vector<float> buzzInputFear;
    vector<int> buzzInputFearCount;
    float maxMoskoEne;
    vector<float> buzzInputFood;
    vector<int> buzzInputFoodCount;
    float maxMoskoDeadEne = 0;
    
public:
    TinyBoss(float initialLife, float initialSize);
    pos move();
    void eat();
    bool reproduce();
    void learnToMove();
    void blink();
    void lookForMoskos(pos moskoPos, float moskoLife);
    void lookForFood(pos moskoPos, float moskoRotten);
};

#endif /* tinyboss_h */
