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
    std::tuple<int, int> gridDimension = std::make_tuple(1, 1);
    pGrid1x1 = new Grid(basePath, gridDimension);
};

void drawGrid(void) {
    pGrid1x1->draw(0);
};
