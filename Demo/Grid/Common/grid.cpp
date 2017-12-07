//
//  grid.cpp
//  GridPoints-iOS
//
//  Created by Hai Nguyen on 12/4/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "grid.h"

enum AttributeLayout {
    ATTRIBUTE_POINT = 0
};

Grid::Grid(std::string basePath, std::tuple<int, int> gridDimension) {
    GLsizei pointsCount = 1; // std::get<0>(gridDimension) * std::get<1>(gridDimension);
    this->points = std::vector<glm::vec2>(pointsCount, glm::vec2(0.0f, 0.0f));
    
    GLuint vertexShaderID = Utility::loadShader(GL_VERTEX_SHADER, basePath + "grid.vsh");
    GLuint fragmentShaderID = Utility::loadShader(GL_FRAGMENT_SHADER, basePath + "grid.fsh");
    
    glBindAttribLocation(programID, ATTRIBUTE_POINT, "aPoint");
    
    Utility::linkShaders(vertexShaderID, fragmentShaderID, programID);
    
    timeUniformLocation = glGetUniformLocation(programID, "uTime");
    
#if GL_APPLE_vertex_array_object
    glGenVertexArraysAPPLE(1, &vertexArrayObject);
    glBindVertexArrayAPPLE(vertexArrayObject);
#elif GL_OES_vertex_array_object
    glGenVertexArraysOES(1, &vertexArrayObject);
    glBindVertexArrayOES(vertexArrayObject);
#endif
    
    glGenBuffers(1, &bufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
    glBufferData(GL_ARRAY_BUFFER, pointsCount * sizeof(glm::vec2), &points.front(), GL_STATIC_DRAW);
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void Grid::draw(time_t deltaTime) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programID);
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(vertexArrayObject);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(vertexArrayObject);
#endif

    glDrawArrays(GL_POINTS, 0, (GLsizei)points.size());
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
};

