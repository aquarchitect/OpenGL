//
//  draw.c
//  OpenGL
//
//  Created by Hai Nguyen on 11/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "common.h"
#include "sample.h"

extern void loadSampleShader(GLuint program);
extern void drawSampleShader(GLuint program);

static GLuint currProgram;

void setup() {
    currProgram = glCreateProgram();
    loadSampleShader(currProgram);
}

void draw() {
    drawSampleShader(currProgram);
}

