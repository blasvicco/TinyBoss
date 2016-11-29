//
//  organism.cpp
//  TinyBoss
//
//  Created by Blas Eugenio Vicco on 11/28/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#include "organism.h"

pos Organism::getPos() {
    return myPos;
}

void Organism::setPos(pos inputPos) {
    myPos = inputPos;
}

float Organism::getLife() {
    return life;
}

void Organism::spendEnergy(float less) {
    life -= less;
}

bool Organism::dead() {
    life--;
    if (life < 0)
        return true;
    return false;
}
