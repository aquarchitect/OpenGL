//
//  draw.c
//  OpenGL
//
//  Created by Hai Nguyen on 11/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "cube.h"
#include "effect.h"
#include <stdio.h>


static GLuint currProgram;


void setup() {
    currProgram = glCreateProgram();
    
//     loadCubeShader(currProgram);
    loadEffectShader(currProgram);
};

void drawCube(const GLfloat transformation[16]) {
//    drawCubeShader(currProgram, transformation);
};

void drawEffect(const GLsizei width, const GLsizei height) {
    const Size resolution = (Size){
        .width = (GLfloat)width,
        .height = (GLfloat)height
    };
    
    drawEffectShader(currProgram, resolution);
}

