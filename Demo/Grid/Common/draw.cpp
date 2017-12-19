//
//  draw.cpp
//  Grid-iOS
//
//  Created by Hai Nguyen on 12/4/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "draw.h"
#include "grid.hpp"

static Grid *pGrid1x1;

void setup(char *basePath, int resolution[2]) {
    pGrid1x1 = new Grid(basePath, vec2(40, 30), vec2(resolution[0], resolution[1]));
};

void draw(float deltaTime) {
    pGrid1x1->draw(deltaTime);
};
