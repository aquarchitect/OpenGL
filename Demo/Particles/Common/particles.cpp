//
//  particles.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "particles.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Utility;

Particles::Particles(string basePath, vec2 grid, vec2 resolution) {
    // indexes
    vector<vec2> vertices(grid[0] * grid[1], {0.0, 0.0});
    
    for (int j = 0; j < grid[1]; j++) {     // y
        for (int i = 0; i < grid[0]; i++) { // x
            int index = j * int(grid[0]) + i;
            vertices[index] = {(GLfloat)i, (GLfloat)j};
        };
    };
    
    this->vertices = vertices;
    this->grid = grid;
    
    linkShaders(basePath + "/particles", program);
    
    resolutionUniformLocation = glGetUniformLocation(program, "uResolution");
    gridUniformLocation = glGetUniformLocation(program, "uGrid");
    
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
    
    GLuint indexAttributeLocation = glGetAttribLocation(program, "aIndex");
    glEnableVertexAttribArray(indexAttributeLocation);
    glVertexAttribPointer(indexAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
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
};
