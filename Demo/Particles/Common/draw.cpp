//
//  particle+.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "draw.h"
#include "update.hpp"
#include "particles.hpp"

static Particles    *pParticle;
static Update       *pUpdate;
static vec2         resolution;

static void setup(char *basePath, int width, int height) {    
    resolution = {width, height};
    pUpdate = new Update(basePath);
    pParticle = new Particles(basePath, vec2(50), resolution);
}

void setup(char *basePath, int resolution[2]) {
    setup(basePath, resolution[0], resolution[1]);
};

void draw(float deltaTime) {
    glViewport(0, 0, resolution[0], resolution[1]);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    pUpdate->draw();
    pParticle->draw();
};
