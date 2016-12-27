//
//  moskitos.cpp
//  TinyBoss
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#include "moskitos.h"

Moskitos::Moskitos(double initialLife, double width, double height) {
    winWidth = width;
    winHeight = height;
    lifeReference = initialLife;
    life = initialLife;
    vector<unsigned int> nppl;
    nppl.clear();
    nppl.push_back(3);
    FlyBrain.ini(2, 2, nppl, TANH, 0.4);
    
    nppl.clear();
    nppl.push_back(3);
    AvoidObstacleBrain.ini(6, 2, nppl, TANH, 0.4);
}

pos Moskitos::move() {
    pos moveTo = myPos;
    chooseTarget();
    if (memoryFoodTarget != -1) {
        pos buzzP = foodPos[memoryFoodTarget];
        vector<double> temp;
        temp.push_back(buzzP.x);
        temp.push_back(buzzP.y);
        moveTo = fly(temp);
        learnToFly(temp);
    }
    return moveTo;
}

void Moskitos::eat() {
    life += 100;
}

bool Moskitos::reproduce() {
    return life > lifeReference * 2;
}

void Moskitos::shakeAvoidObtsacleBrain() {
    vector<unsigned int> nppl;
    nppl.push_back(3);
    AvoidObstacleBrain.ini(6, 2, nppl, TANH, 0);
}

pos Moskitos::avoidObstacle(vector<double> inputs) {
    if (memoryFoodTarget == -1) return myPos;
    
    pos buzzP = foodPos[memoryFoodTarget];
    inputs.push_back(buzzP.x/winWidth);
    inputs.push_back(buzzP.y/winHeight);
    inputs.push_back(myPos.x/winWidth);
    inputs.push_back(myPos.y/winHeight);
    
    pos p;
    AvoidObstacleBrain.setInput(inputs);
    vector<double> output(AvoidObstacleBrain.getOutput());
    p.x = myPos.x + (0.5 * output[0]);
    p.y = myPos.y + (0.5 * output[1]);
    return p;
}

double Moskitos::rotten() {
    return fabsf(life);
}

void Moskitos::blink() {
    maxDelta = 0.0;
    foodDeltas.clear();
    maxFood = 0.0;
    foodAmount.clear();
    foodPos.clear();
}

void Moskitos::lookForFood(pos buzzP, double buzzLife) {
    if (buzzLife > 0) {
        double delta = powf(powf(buzzP.x - myPos.x, 2) + powf(buzzP.y - myPos.y, 2), 0.5);
        maxDelta = delta > maxDelta ? delta : maxDelta;
        foodDeltas.push_back(delta);
        maxFood = buzzLife > maxFood ? buzzLife : maxFood;
        foodAmount.push_back(buzzLife);
        buzzP.x /= winWidth;
        buzzP.y /= winHeight;
        foodPos.push_back(buzzP);
    } else {
        memoryFoodTarget = -1;
    }
}

pos Moskitos::fly(vector<double> inputs) {
    pos p;
    FlyBrain.setInput(inputs);
    vector<double> output(FlyBrain.getOutput());
    p.x = myPos.x + (0.5 * output[0]);
    p.y = myPos.y + (0.5 * output[1]);
    return p;
}

void Moskitos::learnToFly(vector<double> inputs) {
    vector<double> output(FlyBrain.getOutput());
    vector<double> wished = {0, 0, 0, 0};
    vector<double> error = {0, 0, 0, 0};
    if (fabs(inputs[0]) + fabs(inputs[1]) > 0) {
        wished[0] = inputs[0] >= myPos.x/winWidth - 0.005 && inputs[0] <= myPos.x/winWidth + 0.005 ?
            0.0 : ( inputs[0] > myPos.x/winWidth ? 1.0 : -1.0);
        wished[1] = inputs[1] >= myPos.y/winHeight - 0.005 && inputs[1] <= myPos.y/winHeight + 0.005 ?
            0.0 : ( inputs[1] > myPos.y/winHeight ? 1.0 : -1.0);
        //cout << "Inputs: " << inputs[0] << " " << inputs[1] << endl;
        //cout << "Output: " << output[0] << " " << output[1] << endl;
        //cout << "Wished: " << wished[0] << " " << wished[1] << endl;
        error[0] = wished[0] - output[0];
        error[1] = wished[1] - output[1];
        //cout << "Error: " << error[0] << " " << error[1] << endl;
        if (fabs(error[0]) == 2 && fabs(error[1]) == 2) {
            vector<unsigned int> nppl;
            nppl.clear();
            nppl.push_back(4);
            nppl.push_back(6);
            nppl.push_back(3);
            FlyBrain.ini(2, 2, nppl, SIGMOID, 0.2);
        } else {
            FlyBrain.backFix(error);
        }
    }
}

void Moskitos::chooseTarget() {
    foodTarget = -1;
    for (int i = (int)foodDeltas.size() - 1; i >= 0; i--) {
        foodDeltas[i] /= maxDelta > 0 ? maxDelta : 1;
        foodAmount[i] /= maxFood > 0 ? maxFood : 1;
    }
    double max = 0;
    for (int i = 0; i < foodDeltas.size(); i++) {
        if (max < foodDeltas[i] * foodAmount[i]) {
            max =  foodDeltas[i] * foodAmount[i];
            foodTarget = i;
        }
    }
    memoryFoodTarget = memoryFoodTarget > foodDeltas.size() -1 || (memoryFoodTarget == -1 && foodTarget != -1) ? foodTarget : memoryFoodTarget;
    if (memoryFoodTarget != foodTarget) {
        if ((foodAmount[memoryFoodTarget] < 0.0)
            || (foodAmount[foodTarget] - foodAmount[memoryFoodTarget] > 0.2)) {
            memoryFoodTarget = foodTarget;
        }
    }
}

