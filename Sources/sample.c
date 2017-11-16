//
//  sample.c
//  Demo-iOS
//
//  Created by Hai Nguyen on 11/15/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "common.h"
#include "Vertex.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern GLuint loadShader(const GLenum type, const char *filePath);
extern GLuint loadTexture(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid *pixels);
extern void linkProgram(const GLuint program);

GLfloat transformationMatrix[16];
GLfloat projectionMatrix[16];

#if 1 // cube
static const Vertex vertices[] = {
    // Front
    {{1, -1, 1}, {1, 0, 0, 1}},  // 0
    {{1, 1, 1}, {0, 1, 0, 1}},   // 1
    {{-1, 1, 1}, {0, 0, 1, 1}},  // 2
    {{-1, -1, 1}, {0, 0, 0, 1}}, // 3

    // Back
    {{-1, -1, -1}, {1, 0, 0, 1}}, // 4
    {{-1, 1, -1}, {0, 1, 0, 1}},  // 5
    {{1, 1, -1}, {0, 0, 1, 1}},   // 6
    {{1, -1, -1}, {0, 0, 0, 1}},  // 7
};
static const GLubyte indices[] = {
    // Front
    0, 1, 2,
    2, 3, 0,
    // Back
    4, 5, 6,
    6, 7, 4,
    // Left
    3, 2, 5,
    5, 4, 3,
    // Right
    7, 6, 1,
    1, 0, 7,
    // Top
    1, 6, 5,
    5, 2, 1,
    // Bottom
    3, 4, 7,
    7, 0, 3
};
#else // square
static const Vertex vertices[] = {
    {{1, -1, 0}, {1, 0, 0, 1}}, // V0
    {{1, 1, 0}, {0, 1, 0, 1}}, // V1
    {{-1, 1, 0}, {0, 0, 1, 1}}, // V2
    {{-1, -1, 0}, {0, 0, 0, 0}} // V3
};
static const GLubyte indices[] = {
    0, 1, 2,
    2, 3, 0
};
#endif
static GLuint  vertexBuffer;
static GLuint  indexBuffer;
static GLint   _transformationMatrix;
static GLint   _projectionMatrix;
static GLuint  vertexArrayObject;

void loadSampleShader(GLuint program) {
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, "sample.fsh");
    glAttachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);
    
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, "sample.vsh");
    glAttachShader(program, vertexShader);
    glDeleteShader(vertexShader);
    
    glBindAttribLocation(program, VertexAttribPosition, "a_Position");
    glBindAttribLocation(program, VertexAttribColor, "a_Color");
    
    linkProgram(program);
    
    _transformationMatrix = glGetUniformLocation(program, "u_Transformation");
    _projectionMatrix = glGetUniformLocation(program, "u_Projection");
    
    glGenVertexArraysOES(1, &vertexArrayObject);
    glBindVertexArrayOES(vertexArrayObject);
    
    // generate vertex buffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // generate index buffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // enable vertex position buffer
    glEnableVertexAttribArray(VertexAttribPosition);
    glVertexAttribPointer(VertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, Position));
    
    // enable vertex color buffer
    glEnableVertexAttribArray(VertexAttribColor);
    glVertexAttribPointer(VertexAttribColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, Color));
    
    glBindVertexArrayOES(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawSampleShader(GLuint program) {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glUseProgram(program);
    
    glUniformMatrix4fv(_transformationMatrix, 1, GL_FALSE, transformationMatrix);
    glUniformMatrix4fv(_projectionMatrix, 1, GL_FALSE, projectionMatrix);
    
    glBindVertexArrayOES(vertexArrayObject);
    GLsizei count = sizeof(indices) / sizeof(indices[0]);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_BYTE, 0);
    glBindVertexArrayOES(0);
}
