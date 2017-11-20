//
//  effect.c
//  OpenGL
//
//  Created by Hai Nguyen on 11/18/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "common.h"
#include "utility.h"
#include "size.h"
#include <time.h>

static const GLfloat vertices[] = {
    -1.0, -1.0,
    -1.0, +1.0,
    +1.0, -1.0,
    +1.0, +1.0
};

static time_t starTime;
static GLuint vextexAttribute;
static GLuint resolutionUniform;
static GLuint timeUniform;

void loadEffectShader(const GLuint program) {
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, "base.fsh");
    glAttachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);
    
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, "base.vsh");
    glAttachShader(program, vertexShader);
    glDeleteShader(vertexShader);
    
    linkProgram(program);
    
    vextexAttribute = glGetAttribLocation(program, "a_Position");
//    resolutionUniform = glGetUniformLocation(program, "u_Resolution");
//    timeUniform = glGetUniformLocation(program, "u_Time");
    
    glUseProgram(program);
    glEnableVertexAttribArray(vextexAttribute);
    glVertexAttribPointer(vextexAttribute, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glClearColor(0.0, 1.0, 0.0, 1.0);
    // starTime = clock();
}

void drawEffectShader(const GLuint program, const Size resolution) {
    
    glClear(GL_COLOR_BUFFER_BIT);

//    glUniform2f(resolutionUniform, resolution.width, resolution.height);
    // glUniform1f(timeUniform, clock() - starTime);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
