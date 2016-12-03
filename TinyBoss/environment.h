//
//  environment.h
//  TinyBoss
//
//  Created by Blas Eugenio Vicco on 11/9/16.
//  Copyright © 2016 Blas Eugenio Vicco. All rights reserved.
//

#ifndef environment_h
#define environment_h

#include <OpenGL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "tinyboss.h"
#include "moskitos.h"

#define window_width  800
#define window_height 600
#define moskosInitialNumber 30
#define maxMoskosNumber 100
#define bossSize 20
#define moskosSize 2
#define moskosInitialLife 50000
#define bossInitialNumber 3
#define bossInitialLife 80000
#define starvingIndicator 5000

class Environment {
private:
    vector <TinyBoss> Buzz;
    vector <Moskitos> Moskos;
    unsigned int moskosNumber = moskosInitialNumber;
    unsigned int bossNumber = bossInitialNumber;
    
    bool events();
    void main_loop_function(SDL_Window *window);
    void GL_Setup(int width, int height);
    void restartMoskos();
    void restartBoss();
    pos getRandPos(int bodySize);
    pos getNearbyPos(pos p, int size);
    bool samePos(pos a, pos b);
    pos edge(pos moveFrom, pos moveTo, int sizeObj);
    bool collide(pos p, pos moveTo, int size);
    bool onBoss(pos buzzP, pos p);
    pos moveMosko(int i);

public:
    Environment();
    void start();
};

#endif /* environment_h */
