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
    double size;
    vector<double> buzzInputFear;
    vector<int> buzzInputFearCount;
    double maxMoskoEne;
    vector<double> buzzInputFood;
    vector<int> buzzInputFoodCount;
    double maxMoskoDeadEne = 0;
    
public:
    TinyBoss(double initialLife, double initialSize);
    pos move();
    void eat();
    bool reproduce();
    void learnToMove();
    void blink();
    void lookForMoskos(pos moskoPos, double moskoLife);
    void lookForFood(pos moskoPos, double moskoRotten);
};

#endif /* tinyboss_h */
