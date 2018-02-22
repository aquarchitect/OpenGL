//
//  draw.cpp
//  Geometry-iOS
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "draw.h"
#include "scene.hpp"

static scene    *pScene;

void setup(char *basePath, int resolution[2]) {
    pScene = new scene(basePath, {resolution[0], resolution[1]});
};

void rotateCamera(float pitch, float yaw, float roll) {
    pScene->draw();
};

void loadTexture(int width, int height, void *pixels) {
    pScene->loadCubeTexture(width, height, pixels);
};
