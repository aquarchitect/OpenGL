//
//  grid.cpp
//  Grid-iOS
//
//  Created by Hai Nguyen on 12/4/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "grid.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace utility;

Grid::Grid(string basePath, vec2 grid, vec2 resolution) {
    this->vertices = vector<Vertex>(grid[0] * grid[1], {{0.0, 0.0}, 0.0});
    this->grid = grid;
    this->resolution = resolution;
    
    for (int i = 0; i < vertices.size(); ++i) {
        vertices[i].index = i;
    }
    
    linkShaders(basePath + "/grid", program);
    
    timeUniformLocation = glGetUniformLocation(program, "uTime");
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);
    
    GLuint positionAttributeLocation = glGetAttribLocation(program, "aPosition");
    glEnableVertexAttribArray(positionAttributeLocation);
    glVertexAttribPointer(positionAttributeLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, point));
    
    GLuint indexAttributeLocation = glGetAttribLocation(program, "aIndex");
    glEnableVertexAttribArray(indexAttributeLocation);
    glVertexAttribPointer(indexAttributeLocation, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, index));
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void Grid::draw(GLfloat deltaTime) {
    glViewport(0, 0, resolution[0], resolution[1]);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    
    glUniform1f(timeUniformLocation, deltaTime);
    glUniform2fv(resolutionUniformLocation, 1, value_ptr(resolution));
    glUniform2fv(gridUniformLocation, 1, value_ptr(grid));
    
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
