//
//  environment.cpp
//  TinyBoss
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//
#include "environment.h"

Environment::Environment() {
    restartMoskos();
    restartBoss();
}

void Environment::start() {
    int window_flags = SDL_WINDOW_OPENGL;
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Window *window = SDL_CreateWindow("TinyBoss", 0, 0, window_width, window_height, window_flags);
    if (window != NULL) {
        SDL_GLContext glcontext = SDL_GL_CreateContext(window);
        if (glcontext != NULL) {
            GL_Setup(window_width, window_height);
            main_loop_function(window);
            return;
        } else {
            cerr << "Couldn't allocate OpenGL context: " << SDL_GetError() << endl;
            SDL_DestroyWindow(window);
        }
    } else {
        cerr << "Couldn't allocate a window: " << SDL_GetError() << endl;
    }
}

// Process pending events
bool Environment::events() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                return false;
            } break;
        }
    }
    return true;
}

void Environment::main_loop_function(SDL_Window *window) {
    SDL_GL_SetSwapInterval(0);
    while (events()) {
        unsigned int deadCounter = 0;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //CLEAR BOSS DATA
        for (int i = 0; i < bossNumber; i++) Buzz[i].blink();
        
        //FOR EACH MOSKO
        for (int i = 0; i < moskosNumber; i++) {
            bool isDead = Moskos[i].dead();
            deadCounter += isDead ? 1 : 0;
            glLoadIdentity();
            glTranslated(0, 0, 0);
            glBegin (GL_QUADS);
            glColor3ub(255, 0, 0);
            //CLEAR MOSKO DATA
            Moskos[i].blink();
            pos cpos = Moskos[i].getPos();
            //FOR EACH BOSS
            for (int j = 0; j < bossNumber; j++) {
                if (isDead) { // IF MOSKO DEAD
                    glColor3ub(200, 200, 200);
                    if (onBoss(Buzz[j].getPos(), cpos)) { // IF BOOS OVER MOSKO THEN EAT AND ERASE MOSKO
                        Buzz[j].eat();
                        Moskos.erase(Moskos.begin() + i);
                        moskosNumber--;
                    } else { // ELSE ADD DEAD MOSKO TO BOSS DATA
                        Buzz[j].lookForFood(Moskos[i].getPos(), Moskos[i].rotten());
                    }
                } else { // IF MOSKO NOT DEAD
                    // ADD DATA TO MOSKO
                    Moskos[i].lookForFood(Buzz[j].getPos(), Buzz[j].getLife());
                    //ADD DATA TO BOSS
                    Buzz[j].lookForMoskos(Moskos[i].getPos(), Moskos[i].getLife());
                    if (onBoss(Buzz[j].getPos(), cpos)) { // IF MOSKO OVER BOSS THEN SUCK BOSS ENERGY
                        Moskos[i].eat();
                        Buzz[j].spendEnergy(1);
                        glColor3ub(0, 255, 0);
                    }
                }
            }
            
            // MOVE MOSKO
            pos moveTo = moveMosko(i);
            if (!samePos(moveTo, cpos)) {
                Moskos[i].spendEnergy(10);
                Moskos[i].setPos(moveTo);
            }
            
            // REPRODUCE MOSKO
            if (Moskos[i].reproduce() && moskosNumber < maxMoskosNumber) {
                Moskitos *newMosko = new Moskitos(moskosInitialLife, window_width, window_height);
                pos p = Moskos[i].getPos();
                newMosko->setPos(p);
                Moskos.push_back(*newMosko);
                moskosNumber++;
                Moskos[i].spendEnergy(moskosInitialLife/2);
            }
            
            // IF STARVING CHANGE COLOR
            if (Moskos[i].getLife() > 0 && Moskos[i].getLife() < starvingIndicator) glColor3ub(0, 0, 255);
            
            glVertex2f(Moskos[i].getPos().x - moskosSize, Moskos[i].getPos().y + moskosSize);
            glVertex2f(Moskos[i].getPos().x + moskosSize, Moskos[i].getPos().y + moskosSize);
            glVertex2f(Moskos[i].getPos().x + moskosSize, Moskos[i].getPos().y - moskosSize);
            glVertex2f(Moskos[i].getPos().x - moskosSize, Moskos[i].getPos().y - moskosSize);
            glEnd();
        }
        
        pos buzzMoveTo;
        for (int i = 0; i < bossNumber; i++) {
            if (!Buzz[i].dead()) {
                glLoadIdentity();
                glTranslated(0, 0, 0);
                glBegin (GL_QUADS);
                float alpha = Buzz[i].getLife()/bossInitialLife;
                alpha = alpha > 1 ? 1.0 : (alpha < 0 ? 0 : alpha);
                glColor3ub(255*alpha, 255*alpha, 255*alpha);
                buzzMoveTo = Buzz[i].move();
                buzzMoveTo = edge(Buzz[i].getPos(), buzzMoveTo, bossSize);
                bool move = true;
                for (int j = 0; j < bossNumber; j++) {
                    pos p = Buzz[j].getPos();
                    if ( (j != i) &&  collide(p, buzzMoveTo, bossSize)) {
                        move = false;
                        break;
                    }
                }
                buzzMoveTo = move ? buzzMoveTo : Buzz[i].getPos();
                Buzz[i].setPos(buzzMoveTo);
                Buzz[i].learnToMove();
                glVertex2f(buzzMoveTo.x - bossSize, buzzMoveTo.y + bossSize);
                glVertex2f(buzzMoveTo.x + bossSize, buzzMoveTo.y + bossSize);
                glVertex2f(buzzMoveTo.x + bossSize, buzzMoveTo.y - bossSize);
                glVertex2f(buzzMoveTo.x - bossSize, buzzMoveTo.y - bossSize);
                glEnd();
                
                if (Buzz[i].reproduce() && Buzz.size() < 4) {
                    TinyBoss *buxx = new TinyBoss(bossInitialLife, bossSize);
                    pos p = getNearbyPos(Buzz[i].getPos(), moskosSize);
                    if (!samePos(p, Buzz[i].getPos())) {
                        buxx->setPos(p);
                        Buzz.push_back(*buxx);
                        bossNumber++;
                    }
                }
                
            } else {
                bossNumber--;
                Buzz.erase(Buzz.begin() + i);
            }
            
            if (deadCounter == moskosNumber) {
                moskosNumber = 0;
                Moskos.clear();
                restartMoskos();
            }
            
            if (bossNumber == 0) {
                restartBoss();
            }
        }
        SDL_GL_SwapWindow(window);
    }
    
}

// Initialze OpenGL perspective matrix
void Environment::GL_Setup(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glEnable (GL_DEPTH_TEST);
    glOrtho(0, width, 0, height, -10, 10); //take the width and the hieght
    //gluPerspective( 90, (float)width/height, 1, 101 );
    //glOrtho(0.0f, (GLfloat) width, 0.0f, (GLfloat) height, 0.0f, 200.0f);
    glMatrixMode (GL_MODELVIEW);
    //glDepthRange(0.0f, 1.0f);
    glLoadIdentity();
}

void Environment::restartMoskos() {
    for (int i = 0; i < moskosInitialNumber; i++) {
        Moskitos *temp = new Moskitos(moskosInitialLife, window_width, window_height);
        temp->setPos(getRandPos(moskosSize));
        Moskos.push_back(*temp);
    }
    moskosNumber = moskosInitialNumber;
}

void Environment::restartBoss() {
    for (int i = 0; i < bossInitialNumber; i++) {
        TinyBoss *buxx = new TinyBoss(bossInitialLife, bossSize);
        buxx->setPos(getRandPos(bossSize));
        Buzz.push_back(*buxx);
    }
    bossNumber = bossInitialNumber;
}

pos Environment::getRandPos(int bodySize) {
    int offset = 20;
    bodySize = bodySize + offset;
    pos p;
    int max = window_width - bodySize;
    p.x = (rand() % max) + bodySize/2;
    max = window_height - bodySize;
    p.y = (rand() % max) + bodySize/2;
    return p;
}

pos Environment::getNearbyPos(pos p, int size) {
    pos newPos = p;
    for (unsigned int i = -2; i < 3; i++) {
        for (unsigned int j = -2; j < 3; j++) {
            newPos.x = p.x + i; newPos.y = p.y + j;
            for (int l = 0; l < moskosNumber; l++) {
                pos tmp = Moskos[l].getPos();
                if (!collide(tmp, newPos, size)) {
                    newPos = edge(p, newPos, size);
                    if (!samePos(newPos, p)) {
                        return newPos;
                    }
                }
            }
        }
    }
    return newPos;
}

bool Environment::samePos(pos a, pos b) {
    return ( (a.x == b.x) && (a.y == b.y) );
}

pos Environment::edge(pos moveFrom, pos moveTo, int sizeObj) {
    if (moveTo.x + sizeObj >= window_width) moveTo.x = moveFrom.x;
    if (moveTo.x - sizeObj <= 0) moveTo.x = moveFrom.x;
    if (moveTo.y + sizeObj >= window_height) moveTo.y = moveFrom.y;
    if (moveTo.y - sizeObj <= 0) moveTo.y = moveFrom.y;
    return moveTo;
}

bool Environment::collide(pos p, pos moveTo, int size) {
    return (((p.x - 2 * size <= moveTo.x) && (p.x + 2 * size >= moveTo.x))
            && ((p.y - 2 * size <= moveTo.y) && (p.y + 2 * size >= moveTo.y)));
}

bool Environment::onBoss(pos buzzP, pos p) {
    return (((buzzP.x - bossSize - moskosSize < p.x) && (buzzP.x + bossSize + moskosSize > p.x))
            && ((buzzP.y - bossSize - moskosSize < p.y) && (buzzP.y + bossSize + moskosSize > p.y)));
}

pos Environment::moveMosko(int i) {
    pos moveTo = Moskos[i].getPos();
    if (!Moskos[i].dead()) {
        moveTo = Moskos[i].move();
        int c = 5;
        bool move = false;
        while (c > 0 && !move) {
            for (int j = 0; j < moskosNumber; j++) {
                pos p = Moskos[j].getPos();
                if ( (j != i) &&  collide(p, moveTo, moskosSize)) {
                    if (c == 3) Moskos[i].shakeAvoidObtsacleBrain();
                    vector<double> inputToAvoidObstacle;
                    inputToAvoidObstacle.push_back(p.x/window_width);
                    inputToAvoidObstacle.push_back(p.y/window_height);
                    moveTo = Moskos[i].avoidObstacle(inputToAvoidObstacle);
                    moveTo = edge(Moskos[i].getPos(), moveTo, moskosSize);
                    move = false;
                    continue;
                } else {
                    move = true;
                }
            }
            c--;
        }
        moveTo = move ? moveTo : Moskos[i].getPos();
        moveTo = edge(Moskos[i].getPos(), moveTo, moskosSize);
    }
    return moveTo;
}
