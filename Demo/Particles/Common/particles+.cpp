//
//  particle+.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "particles.h"
#include "update.hpp"

static Particles    *particle;
static Update       *update;
static vec2         _resolution;

void setupParticles(char *basePath, int resolution[2]) {
    const GLsizei count = 1024 * 3; // number of particles
    vec2 grid(ceil(sqrt(count)), floor(sqrt(count)));

    _resolution = {resolution[0], resolution[1]};
    particle = new Particles(basePath, grid, _resolution);
    update = new Update(basePath, grid, _resolution);
};

void drawParticles(float deltaTime) {
    glViewport(0, 0, _resolution[0], _resolution[1]);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    update->draw();
    particle->draw();
};
