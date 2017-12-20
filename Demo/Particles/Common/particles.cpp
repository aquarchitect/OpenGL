//
//  particles.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "particles.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Utility;

GLuint Particles::createTexture(GLuint slot, GLvoid *pixels) {
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)grid.x, (GLsizei)grid.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    
    return texture;
};

Particles::Particles(string basePath, vec2 grid, vec2 resolution) {
    this->grid = grid;
    
    // indexes
    int count = grid[0] * grid[1];
    vector<vec2> vertices(count, {0.0, 0.0});
    RGBA rgbaP0[count];
    RGBA rgbaV0[count];
    
    // another thought was to randomize the initial values on the GPU.
    // however, as glVertexID is not available on OpenGL ES 2.0, indexes
    // initialization cannot be avoided. Instead of seprating process
    // the pixel data is also be randomize through the loop.
    for (int j = 0; j < grid.y; j++) {
        for (int i = 0; i < grid.x; i++) { // x
            int index = j * int(grid.x) + i;
            
            vertices[index] = {
                GLfloat(i/grid.x),
                GLfloat(j/grid.y)
            };
            
            rgbaP0[index] = {
                GLubyte(fmod(rand(), 255.0)),
                GLubyte(fmod(rand(), 255.0)),
                GLubyte(fmod(rand(), 255.0)),
                GLubyte(fmod(rand(), 255.0))
            };
        };
    };
    
    this->vertices = vertices;
    this->textures.p0 = createTexture(0, rgbaP0);
    this->textures.v0 = createTexture(1, NULL);
    this->textures.p1 = createTexture(2, NULL);
    this->textures.v1 = createTexture(3, NULL);
    
    linkShaders(basePath + "/particles", program);
    
    resolutionUniformLocation = glGetUniformLocation(program, "uResolution");
    gridUniformLocation = glGetUniformLocation(program, "uGrid");
    positionUniformLocation = glGetUniformLocation(program, "uPosition");
    
#if GL_APPLE_vertex_array_object
    glGenVertexArraysAPPLE(1, &VAO);
    glBindVertexArrayAPPLE(VAO);
#elif GL_OES_vertex_array_object
    glGenVertexArraysOES(1, &VAO);
    glBindVertexArrayOES(VAO);
#endif
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices.front(), GL_STATIC_DRAW);
    
    GLuint texCoordAttributeLocation = glGetAttribLocation(program, "aTexCoord");
    glEnableVertexAttribArray(texCoordAttributeLocation);
    glVertexAttribPointer(texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif

    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void Particles::draw() {
    glUseProgram(program);

    glUniform2fv(gridUniformLocation, 1, value_ptr(grid));
    glUniform2fv(resolutionUniformLocation, 1, value_ptr(resolution));
    
    glBindTexture(GL_TEXTURE_2D, textures.p0);
    glUniform1i(positionUniformLocation, 0);
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(VAO);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(VAO);
#endif

    glDrawArrays(GL_POINTS, 0, GLsizei(vertices.size()));

#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
    
    glBindTexture(GL_TEXTURE_2D, 0);
};
