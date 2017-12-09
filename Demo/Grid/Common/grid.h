//
//  grid.h
//  GridPoints-iOS
//
//  Created by Hai Nguyen on 12/4/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef grid_hpp
#define grid_hpp

// grid.cpp
#ifdef __cplusplus
#include "utility.hpp"
#include <string>
#include <vector>
#include <glm/glm.hpp>

class Grid {
public:
    Grid(std::string basePath, glm::vec2 gridSize);
    void            draw(time_t deltaTime, glm::vec2 resolution);
private:
    struct Vertex {
        GLfloat point[2];
        GLfloat index;
    };
    
    std::vector<Vertex>     vertices;
    glm::vec2               gridSize;
    
    const GLuint            programID = glCreateProgram();
    
    GLuint                  vertexArrayObject;
    GLuint                  bufferObject;
    
    GLuint                  timeUniformLocation;
    GLuint                  resolutionUniformLocation;
    GLuint                  gridSizeUniformLocation;
};
#endif /* __cplusplus */

// grid+.cpp
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    extern void setupGrid(char *basePath);
    extern void drawGrid(float deltaTime, int resolutionWidth, int resolutionHeight);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* grid_h */
