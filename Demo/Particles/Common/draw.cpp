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
#include "obstacles.hpp"
#include "textures.hpp"

static Particles    *pParticle;
static Update       *pUpdate;
static Textures     *pTextures;
static Obstacles    *pObstacles;
static vec2         resolution;

static void setup(char *basePath, int width, int height) {    
    resolution = {width, height};
    vec2 size(32.0);
    
    pTextures = new Textures(basePath, size, resolution);
    pUpdate = new Update(basePath, size, resolution, pTextures);
    pParticle = new Particles(basePath, size, resolution, pTextures);
    pObstacles = new Obstacles(basePath, resolution, pTextures);
}

void setup(char *basePath, int resolution[2]) {
    setup(basePath, resolution[0], resolution[1]);
};

void draw(float deltaTime) {
    pUpdate->draw();
    pParticle->draw();
    pObstacles->draw(false);
};

void addObstacle(int x, int y) {
    pObstacles->addObstacle(vec2(x, y));
};
