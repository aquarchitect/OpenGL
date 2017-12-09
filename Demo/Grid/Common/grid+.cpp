//
//  grid+.cpp
//  GridPoints-iOS
//
//  Created by Hai Nguyen on 12/4/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "grid.h"

static Grid     *pGrid1x1;

void setupGrid(char *basePath) {
    pGrid1x1 = new Grid(basePath, glm::vec2(80, 50));
};

void drawGrid(float deltaTime, int resolutionWidth, int resolutionHeight) {
    pGrid1x1->draw(deltaTime, glm::vec2(resolutionWidth, resolutionHeight));
};
