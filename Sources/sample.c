//
//  sample.c
//  Demo-iOS
//
//  Created by Hai Nguyen on 11/15/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "sample.h"
#include "Vertex.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern void attachShader(GLuint program, GLenum type, const char *filePath);
extern void linkProgram(GLuint program);

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
GLfloat transformMatrix[16];

static GLuint  vertexBuffer;
static GLuint  indexBuffer;
static GLint   uniformMatrix;
static GLuint  vertexArrayObject;

void loadSampleShader(GLuint program) {
    attachShader(program, GL_FRAGMENT_SHADER, "sample.fsh");
    attachShader(program, GL_VERTEX_SHADER, "sample.vsh");
    
    glBindAttribLocation(program, VertexAttribPosition, "a_Position");
    glBindAttribLocation(program, VertexAttribColor, "a_Color");
    
    linkProgram(program);
    
    uniformMatrix = glGetUniformLocation(program, "u_Transform");
    
    glGenVertexArraysOES(1, &vertexArrayObject);
    glBindVertexArrayOES(vertexArrayObject);
    
    // generate vertex buffer;
    glGenBuffers(1, &(vertexBuffer));
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
    glUseProgram(program);
    
    glUniformMatrix4fv(uniformMatrix, 1, GL_FALSE, transformMatrix);
    
    glBindVertexArrayOES(vertexArrayObject);
    GLsizei count = sizeof(indices) / sizeof(indices[0]);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_BYTE, 0);
    glBindVertexArrayOES(0);
}
