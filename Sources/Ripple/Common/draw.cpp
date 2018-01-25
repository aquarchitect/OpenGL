//
//  draw.cpp
//  Ripple-iOS
//
//  Created by Hai Nguyen on 1/19/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

#include "draw.h"
#include "flat.hpp"

static Flat     *pFlat;

void setup(char *basePath, int resolution[2]) {
    pFlat = new Flat(basePath, {resolution[0], resolution[1]});
};

void draw(float deltaTime) {
    pFlat->draw(deltaTime);
};

void loadTexture(int texture) {
    pFlat->loadTexture(texture);
};
