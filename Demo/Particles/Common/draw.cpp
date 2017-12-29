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
#include "textures.hpp"

static Particles    *pParticle;
static Update       *pUpdate;
static Textures     *pTextures;
static vec2         resolution;

static void setup(char *basePath, int width, int height) {    
    resolution = {width, height};
    vec2 grid(32.0);
    
    pTextures = new Textures(basePath, grid);
    pUpdate = new Update(basePath, grid, resolution, pTextures);
    pParticle = new Particles(basePath, grid, resolution, pTextures);
}

void setup(char *basePath, int resolution[2]) {
    setup(basePath, resolution[0], resolution[1]);
};

void draw(float deltaTime) {
    pUpdate->draw();
    pParticle->draw();
};
