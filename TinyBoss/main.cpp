//
//  main.cpp
//  TinyBoss
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#include <iostream>
#include <time.h>
#include "environment.h"

using namespace std;

int main() {
    srand((int)(time(0)));
    Environment Env = Environment();
    Env.start();
    
    return 0;
}
