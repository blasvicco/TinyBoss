//
//  boos.cpp
//  TinyBoss
//
//  Created by Blas Eugenio Vicco on 11/26/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#include "tinyboss.h"

TinyBoss::TinyBoss(double initialLife, double initialSize) {
    lifeReference = initialLife;
    life = initialLife;
    size = initialSize;
    
    vector<unsigned int> nppl;
    nppl.push_back(6);
    nppl.push_back(8);
    nppl.push_back(5);
    FearBrain.ini(4, 4, nppl, TANH, 0);
    FoodBrain.ini(4, 4, nppl, TANH, 0);

    blink();
}

pos TinyBoss::move() {
    for (int i = 0; i < 4; i++) {
        if (buzzInputFearCount[i] != 0) {
            buzzInputFear[i] /= buzzInputFearCount[i];
            buzzInputFear[i] /= maxMoskoEne;
        }
        if (buzzInputFood[i] != 0) {
            buzzInputFood[i] /= buzzInputFoodCount[i];
            buzzInputFood[i] /= maxMoskoDeadEne;
        }
    }
    pos p = myPos;
    FearBrain.setInput(buzzInputFear);
    FoodBrain.setInput(buzzInputFood);
    vector<double> fearOutput(FearBrain.getOutput());
    vector<double> foodOutput(FoodBrain.getOutput());
    //cout << "F Input: " << buzzInputFear[0] << " " << buzzInputFear[1] << " " << buzzInputFear[2] << " " << buzzInputFear[3] << endl;
    //cout << "F Input: " << fearOutput[0] << " " << fearOutput[1] << " " << fearOutput[2] << " " << fearOutput[3] << endl;
    if (fabs(buzzInputFear[0]) + fabs(buzzInputFear[1]) + fabs(buzzInputFear[2]) + fabs(buzzInputFear[3]) > 0) {
        p.x += (0.3 * (fearOutput[1] + fearOutput[3]));
        p.y += (0.3 * (fearOutput[0] + fearOutput[2]));
    }
    //cout << "F Input: " << buzzInputFood[0] << " " << buzzInputFood[1] << " " << buzzInputFood[2] << " " << buzzInputFood[3] << endl;
    //cout << "F Output: " << foodOutput[0] << " " << foodOutput[1] << " " << foodOutput[2] << " " << foodOutput[3] << endl;
    if (fabs(buzzInputFood[0]) + fabs(buzzInputFood[1]) + fabs(buzzInputFood[2]) + fabs(buzzInputFood[3]) > 0) {
        p.x += (0.8 * (foodOutput[1] + foodOutput[3]));
        p.y += (0.8 * (foodOutput[0] + foodOutput[2]));
    }
    return p;
}

void TinyBoss::eat() {
    life += 10000;
}

bool TinyBoss::reproduce() {
    return false;//(life < lifeReference/3);
}

void TinyBoss::learnToMove() {
    vector<double> fearOutput(FearBrain.getOutput());
    vector<double> foodOutput(FoodBrain.getOutput());
    vector<double> wished = {0, 0, 0, 0};
    vector<double> error = {0, 0, 0, 0};
    if (fabs(buzzInputFear[0]) + fabs(buzzInputFear[1]) + fabs(buzzInputFear[2]) + fabs(buzzInputFear[3]) > 0) {
        wished[0] = buzzInputFear[0] == buzzInputFear[2] ? 0 : (buzzInputFear[0] > buzzInputFear[2] ? -1.0 : 1.0);
        wished[1] = buzzInputFear[1] == buzzInputFear[3] ? 0 : (buzzInputFear[1] > buzzInputFear[3] ? -1.0 : 1.0);
        wished[2] = buzzInputFear[0] == buzzInputFear[2] ? 0 : (buzzInputFear[2] > buzzInputFear[0] ? 1.0 : -1.0);
        wished[3] = buzzInputFear[1] == buzzInputFear[3] ? 0 : (buzzInputFear[3] > buzzInputFear[1] ? 1.0 : -1.0);
        error[0] = wished[0] - fearOutput[0];
        error[1] = wished[1] - fearOutput[1];
        error[2] = wished[2] - fearOutput[2];
        error[3] = wished[3] - fearOutput[3];
        FearBrain.backFix(error);
    }
    
    //cout << "F buzzInputFood: " << buzzInputFood[0] << " " << buzzInputFood[1] << " " << buzzInputFood[2] << " " << buzzInputFood[3] << endl;
    if (fabs(buzzInputFood[0]) + fabs(buzzInputFood[1]) + fabs(buzzInputFood[2]) + fabs(buzzInputFood[3]) > 0) {
        wished[0] = buzzInputFood[0] == buzzInputFood[2] ? 0 : (buzzInputFood[0] > buzzInputFood[2] ? 1.0 : -1.0);
        wished[1] = buzzInputFood[1] == buzzInputFood[3] ? 0 : (buzzInputFood[1] > buzzInputFood[3] ? 1.0 : -1.0);
        wished[2] = buzzInputFood[0] == buzzInputFood[2] ? 0 : (buzzInputFood[2] > buzzInputFood[0] ? -1.0 : 1.0);
        wished[3] = buzzInputFood[1] == buzzInputFood[3] ? 0 : (buzzInputFood[3] > buzzInputFood[1] ? -1.0 : 1.0);
        //cout << "F Wished: " << wished[0] << " " << wished[1] << " " << wished[2] << " " << wished[3] << endl;
        error[0] = wished[0] - foodOutput[0];
        error[1] = wished[1] - foodOutput[1];
        error[2] = wished[2] - foodOutput[2];
        error[3] = wished[3] - foodOutput[3];
        //cout << "F Error: " << error[0] << " " << error[1] << " " << error[2] << " " << error[3] << endl;
        FoodBrain.backFix(error);
    }
}

void TinyBoss::blink() {
    buzzInputFearCount = {0, 0, 0, 0};
    buzzInputFear = {0, 0, 0, 0};
    maxMoskoEne = 0.0;
    
    buzzInputFoodCount = {0, 0, 0, 0};
    buzzInputFood = {0, 0, 0, 0};
    maxMoskoDeadEne = 0.0;
}

void TinyBoss::lookForMoskos(pos moskoPos, double moskoLife) {
    if ( ((moskoPos.y > myPos.y) && (moskoPos.y < myPos.y + size*3))
        && ((moskoPos.x >= myPos.x - size*1.5) && (moskoPos.x <= myPos.x + size*1.5)) ) {
        //up
        if (maxMoskoEne < moskoLife) maxMoskoEne = moskoLife;
        buzzInputFear[0] += moskoLife;
        buzzInputFearCount[0]++;
    }
    
    if ( ((moskoPos.x > myPos.x) && (moskoPos.x < myPos.x + size*3))
        && ((moskoPos.y >= myPos.y - size*1.5) && (moskoPos.y <= myPos.y + size*1.5)) ) {
        //right
        if (maxMoskoEne < moskoLife) maxMoskoEne = moskoLife;
        buzzInputFear[1] += moskoLife;
        buzzInputFearCount[1]++;
    }
    
    if ( ((moskoPos.y < myPos.y) && (moskoPos.y > myPos.y - size*3))
        && ((moskoPos.x >= myPos.x - size*1.5) && (moskoPos.x <= myPos.x + size*1.5)) ) {
        //down
        if (maxMoskoEne < moskoLife) maxMoskoEne = moskoLife;
        buzzInputFear[2] += moskoLife;
        buzzInputFearCount[2]++;
    }
    
    if ( ((moskoPos.x < myPos.x) && (moskoPos.x > myPos.x - size*3))
        && ((moskoPos.y >= myPos.y - size*1.5) && (moskoPos.y <= myPos.y + size*1.5)) ) {
        //left
        if (maxMoskoEne < moskoLife) maxMoskoEne = moskoLife;
        buzzInputFear[3] += moskoLife;
        buzzInputFearCount[3]++;
    }
}

void TinyBoss::lookForFood(pos moskoPos, double moskoRotten) {
    if ( ((moskoPos.y > myPos.y+size) && (moskoPos.y < myPos.y + size*16))
        && ((moskoPos.x >= myPos.x - size*4) && (moskoPos.x <= myPos.x + size*4)) ) {
        //up
        if (maxMoskoDeadEne < moskoRotten) maxMoskoDeadEne = moskoRotten;
        buzzInputFood[0] += moskoRotten;
        buzzInputFoodCount[0]++;
    }
    
    if ( ((moskoPos.x > myPos.x+size) && (moskoPos.x < myPos.x + size*16))
        && ((moskoPos.y >= myPos.y - size*4) && (moskoPos.y <= myPos.y + size*4)) ) {
        //right
        if (maxMoskoDeadEne < moskoRotten) maxMoskoDeadEne = moskoRotten;
        buzzInputFood[1] += moskoRotten;
        buzzInputFoodCount[1]++;
    }
    
    if ( ((moskoPos.y < myPos.y+size) && (moskoPos.y > myPos.y - size*16))
        && ((moskoPos.x >= myPos.x - size*4) && (moskoPos.x <= myPos.x + size*4)) ) {
        //down
        if (maxMoskoDeadEne < moskoRotten) maxMoskoDeadEne = moskoRotten;
        buzzInputFood[2] += moskoRotten;
        buzzInputFoodCount[2]++;
    }
    
    if ( ((moskoPos.x < myPos.x+size) && (moskoPos.x > myPos.x - size*16))
        && ((moskoPos.y >= myPos.y - size*4) && (moskoPos.y <= myPos.y + size*4)) ) {
        //left
        if (maxMoskoDeadEne < moskoRotten) maxMoskoDeadEne = moskoRotten;
        buzzInputFood[3] += moskoRotten;
        buzzInputFoodCount[3]++;
    }
}
