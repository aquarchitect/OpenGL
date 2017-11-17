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
    {{ 1, -1, 1}, {1, 0, 0, 1}, {1, 0}, {0, 0, 1}}, // 0
    {{ 1,  1, 1}, {0, 1, 0, 1}, {1, 1}, {0, 0, 1}}, // 1
    {{-1,  1, 1}, {0, 0, 1, 1}, {0, 1}, {0, 0, 1}}, // 2
    {{-1, -1, 1}, {0, 0, 0, 1}, {0, 0}, {0, 0, 1}}, // 3
    
    // Back
    {{-1, -1, -1}, {0, 0, 1, 1}, {1, 0}, {0, 0, -1}}, // 4
    {{-1,  1, -1}, {0, 1, 0, 1}, {1, 1}, {0, 0, -1}}, // 5
    {{ 1,  1, -1}, {1, 0, 0, 1}, {0, 1}, {0, 0, -1}}, // 6
    {{ 1, -1, -1}, {0, 0, 0, 1}, {0, 0}, {0, 0, -1}}, // 7
    
    // Left
    {{-1, -1,  1}, {1, 0, 0, 1}, {1, 0}, {-1, 0, 0}}, // 8
    {{-1,  1,  1}, {0, 1, 0, 1}, {1, 1}, {-1, 0, 0}}, // 9
    {{-1,  1, -1}, {0, 0, 1, 1}, {0, 1}, {-1, 0, 0}}, // 10
    {{-1, -1, -1}, {0, 0, 0, 1}, {0, 0}, {-1, 0, 0}}, // 11
    
    // Right
    {{1, -1, -1}, {1, 0, 0, 1}, {1, 0}, {1, 0, 0}}, // 12
    {{1,  1, -1}, {0, 1, 0, 1}, {1, 1}, {1, 0, 0}}, // 13
    {{1,  1,  1}, {0, 0, 1, 1}, {0, 1}, {1, 0, 0}}, // 14
    {{1, -1,  1}, {0, 0, 0, 1}, {0, 0}, {1, 0, 0}}, // 15
    
    // Top
    {{ 1, 1,  1}, {1, 0, 0, 1}, {1, 0}, {0, 1, 0}}, // 16
    {{ 1, 1, -1}, {0, 1, 0, 1}, {1, 1}, {0, 1, 0}}, // 17
    {{-1, 1, -1}, {0, 0, 1, 1}, {0, 1}, {0, 1, 0}}, // 18
    {{-1, 1,  1}, {0, 0, 0, 1}, {0, 0}, {0, 1, 0}}, // 19
    
    // Bottom
    {{ 1, -1, -1}, {1, 0, 0, 1}, {1, 0}, {0, -1, 0}}, // 20
    {{ 1, -1,  1}, {0, 1, 0, 1}, {1, 1}, {0, -1, 0}}, // 21
    {{-1, -1,  1}, {0, 0, 1, 1}, {0, 1}, {0, -1, 0}}, // 22
    {{-1, -1, -1}, {0, 0, 0, 1}, {0, 0}, {0, -1, 0}}, // 23
};
static const GLubyte indices[] = {
    // Front
    0, 1, 2,
    2, 3, 0,
    
    // Back
    4, 5, 6,
    6, 7, 4,
    
    // Left
    8, 9, 10,
    10, 11, 8,
    
    // Right
    12, 13, 14,
    14, 15, 12,
    
    // Top
    16, 17, 18,
    18, 19, 16,
    
    // Bottom
    20, 21, 22,
    22, 23, 20
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
static GLuint  textureBuffer;
static GLuint  vertexBuffer;
static GLuint  indexBuffer;
static GLuint  vertexArrayObject;
static GLuint  transformationUniform;
static GLuint  projectionUniform;
static GLuint  textureUniform;

static GLuint  lightColorUniform;
static GLuint  lightDirectionUniform;
static GLuint  lightAmbientIntensityUniform;
static GLuint  lightDiffuseIntensityUniform;

void setFacadeImage(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid *pixels) {
    textureBuffer = loadTexture(width, height, type, pixels);
}

void loadSampleShader(GLuint program) {
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, "sample.fsh");
    glAttachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);
    
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, "sample.vsh");
    glAttachShader(program, vertexShader);
    glDeleteShader(vertexShader);
    
    glBindAttribLocation(program, VertexAttribPosition, "a_Position");
    glBindAttribLocation(program, VertexAttribColor, "a_Color");
    glBindAttribLocation(program, VertexAttribTexCoord, "a_TexCoord");
    glBindAttribLocation(program, VertexAttribNormal, "a_Normal");
    
    linkProgram(program);
    
    transformationUniform = glGetUniformLocation(program, "u_Transformation");
    projectionUniform = glGetUniformLocation(program, "u_Projection");
    textureUniform = glGetUniformLocation(program, "u_Texture");
    
    lightColorUniform = glGetUniformLocation(program, "u_Light.color");
    lightDirectionUniform = glGetUniformLocation(program, "u_Light.direction");
    lightAmbientIntensityUniform = glGetUniformLocation(program, "u_Light.ambientIntensity");
    lightDiffuseIntensityUniform = glGetUniformLocation(program, "u_Light.diffuseIntensity");

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
    glVertexAttribPointer(VertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, position));
    
    // enable vertex color buffer
    glEnableVertexAttribArray(VertexAttribColor);
    glVertexAttribPointer(VertexAttribColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, color));
    
    // enable texture coordinate buffer
    glEnableVertexAttribArray(VertexAttribTexCoord);
    glVertexAttribPointer(VertexAttribTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, texCoord));
    
    // enabled normal buffer
    glEnableVertexAttribArray(VertexAttribNormal);
    glVertexAttribPointer(VertexAttribNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, normal));
    
    glBindVertexArrayOES(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawSampleShader(GLuint program) {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(program);
    
    glUniformMatrix4fv(transformationUniform, 1, GL_FALSE, transformationMatrix);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, projectionMatrix);
    
    // enable texture
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureBuffer);
    glUniform1i(textureUniform, 1);
    
    glUniform3f(lightColorUniform, 1, 1, 1);
    glUniform3f(lightDirectionUniform, 0, -1, -1);
    glUniform1f(lightAmbientIntensityUniform, 0.3);
    glUniform1f(lightDiffuseIntensityUniform, 0.8);
    
    glBindVertexArrayOES(vertexArrayObject);
    GLsizei count = sizeof(indices) / sizeof(indices[0]);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_BYTE, 0);
    glBindVertexArrayOES(0);
}
