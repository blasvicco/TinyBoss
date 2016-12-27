//
//  random.cpp
//  test
//
//  Created by Blas Eugenio Vicco on 12/23/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#include "random.h"

int Random::sign() {
    const unsigned int rangeFrom = 0;
    const unsigned int rangeTo = 1;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(rangeFrom, rangeTo);
    return distr(generator) == 0 ? -1 : 1;
}

int Random::onoff() {
    const unsigned int rangeFrom = 0;
    const unsigned int rangeTo = 1;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(rangeFrom, rangeTo);
    return distr(generator);
}

double Random::dur01() {
    const unsigned int rangeFrom = 0;
    const unsigned int rangeTo = 10000;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(rangeFrom, rangeTo);
    return (double)distr(generator)/(double)rangeTo;
}
