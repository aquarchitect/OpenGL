//
//  draw.c
//  OpenGL
//
//  Created by Hai Nguyen on 11/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "draw.h"

static GLuint currProgram;

void setup() {
    currProgram = glCreateProgram();
    loadCubeShader(currProgram);
};

void drawCube(const GLfloat transformation[16]) {
    drawCubeShader(currProgram, transformation);
};
