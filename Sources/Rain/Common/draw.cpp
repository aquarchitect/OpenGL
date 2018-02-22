//
//  particle+.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "draw.h"
#include "rain.hpp"
//#include "update.hpp"
//#include "particles.hpp"
//#include "obstacles.hpp"
//#include "textures.hpp"

//static Particles    *pParticle;
//static Update       *pUpdate;
//static Textures     *pTextures;
//static Obstacles    *pObstacles;
//static vec2         resolution;

static rain *pRain;

void setup(char *basePath, int resolution[2]) {
    pRain = new rain(basePath, vec2(64.0), {resolution[0], resolution[1]});
};

void draw(float deltaTime) {
    pRain->draw();
};

void addObstacle(int x, int y) {
    pRain->addObstacle({x, y});
};
