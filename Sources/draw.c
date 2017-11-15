//
//  draw.c
//  OpenGL
//
//  Created by Hai Nguyen on 11/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "common.h"
#include "sample.h"

static GLuint currProgram;

void setup() {
    currProgram = glCreateProgram();
    loadSampleShader(currProgram);
}

void draw() {
    drawSampleShader(currProgram);
}

