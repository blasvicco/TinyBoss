//
//  organism.hpp
//  TinyBoss
//
//  Created by Blas Eugenio Vicco on 11/28/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#ifndef organism_h
#define organism_h

#include "net.h"

struct pos {
    float x;
    float y;
};


class Organism {
private:
    
protected:
    pos myPos;
    float lifeReference;
    float life;
    
public:
    pos getPos();
    void setPos(pos inputPos);
    float getLife();
    void spendEnergy(float less);
    bool dead();
    virtual pos move() = 0;
    virtual void eat() = 0;
    virtual bool reproduce() = 0;
};

#endif /* organism_h */
