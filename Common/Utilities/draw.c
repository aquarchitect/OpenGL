//
//  draw.c
//  OpenGL
//
//  Created by Hai Nguyen on 11/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "common.h"
#include "cube.h"

extern void loadCubeShader(GLuint program);
extern void drawCubeShader(GLuint program);

static GLuint currProgram;

void setup() {
    currProgram = glCreateProgram();
    loadCubeShader(currProgram);
}

void draw() {
    drawCubeShader(currProgram);
}

