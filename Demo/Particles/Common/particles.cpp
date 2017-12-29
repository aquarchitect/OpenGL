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

Particles::Particles(string basePath, vec2 grid, vec2 resolution, Textures *textures) {
    vector<vec2> vertices(grid[0] * grid[1], {0.0, 0.0});
    for (int j = 0; j < grid.y; j++) {
        for (int i = 0; i < grid.x; i++) { // x
            int index = j * int(grid.x) + i;
            
            vertices[index] = {
                GLfloat(i/grid.x),
                GLfloat(j/grid.y)
            };
        };
    };
    
    this->textures = textures;
    this->grid = grid;
    this->resolution = resolution;
    this->vertices = vertices;
    
    linkShaders(basePath + "/particles", program);
    
    resolutionUniformLocation = glGetUniformLocation(program, "uResolution");
    positionsUniformLocation = glGetUniformLocation(program, "uPositions");
    velocitiesUniformLocation = glGetUniformLocation(program, "uVelocities");
    
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
    //glBindFramebuffer(GL_FRAMEBUFFER, 1);
    glViewport(0, 0, resolution.x, resolution.y);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glUseProgram(program);

    glUniform2fv(resolutionUniformLocation, 1, value_ptr(resolution));
    
    glBindTexture(GL_TEXTURE_2D, textures->p0);
    glUniform1i(positionsUniformLocation, 1);
    
    glBindTexture(GL_TEXTURE_2D, textures->v0);
    glUniform1i(velocitiesUniformLocation, 2);
    
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
