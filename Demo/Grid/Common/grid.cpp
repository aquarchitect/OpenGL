//
//  grid.cpp
//  GridPoints-iOS
//
//  Created by Hai Nguyen on 12/4/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "grid.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum AttributeLayout {
    ATTRIBUTE_POINT = 0,
    ATTRIBUTE_INDEX
};

Grid::Grid(std::string basePath, glm::vec2 gridSize) {
    this->vertices = std::vector<Vertex>(gridSize[0] * gridSize[1], {{0.0, 0.0}, 0.0});
    this->gridSize = gridSize;
    
    for (int i = 0; i < vertices.size(); ++i) {
        vertices[i].index = i;
    }
    
    GLuint vertexShaderID = Utility::loadShader(GL_VERTEX_SHADER, basePath + "grid.vsh");
    GLuint fragmentShaderID = Utility::loadShader(GL_FRAGMENT_SHADER, basePath + "grid.fsh");
    
    glBindAttribLocation(programID, ATTRIBUTE_POINT, "aPoint");
    glBindAttribLocation(programID, ATTRIBUTE_INDEX, "aIndex");
    
    Utility::linkShaders(vertexShaderID, fragmentShaderID, programID);
    
    timeUniformLocation = glGetUniformLocation(programID, "uTime");
    resolutionUniformLocation = glGetUniformLocation(programID, "uResolution");
    gridSizeUniformLocation = glGetUniformLocation(programID, "uGridSize");
    
#if GL_APPLE_vertex_array_object
    glGenVertexArraysAPPLE(1, &vertexArrayObject);
    glBindVertexArrayAPPLE(vertexArrayObject);
#elif GL_OES_vertex_array_object
    glGenVertexArraysOES(1, &vertexArrayObject);
    glBindVertexArrayOES(vertexArrayObject);
#endif
    
    glGenBuffers(1, &bufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(ATTRIBUTE_POINT);
    glVertexAttribPointer(ATTRIBUTE_POINT, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, point));
    
    glEnableVertexAttribArray(ATTRIBUTE_INDEX);
    glVertexAttribPointer(ATTRIBUTE_INDEX, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, index));
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void Grid::draw(GLfloat deltaTime, glm::vec2 resolution) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programID);
    
    glUniform1f(timeUniformLocation, deltaTime);
    glUniform2fv(resolutionUniformLocation, 1, glm::value_ptr(resolution));
    glUniform2fv(gridSizeUniformLocation, 1, glm::value_ptr(gridSize));
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(vertexArrayObject);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(vertexArrayObject);
#endif

    glDrawArrays(GL_POINTS, 0, (GLsizei)vertices.size());

#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
};

