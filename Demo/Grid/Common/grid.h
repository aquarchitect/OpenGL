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
    Grid(string basePath, vec2 grid);
    void            draw(GLfloat deltaTime, vec2 resolution);
private:
    struct Vertex {
        GLfloat point[2];
        GLfloat index;
    };
    
    vector<Vertex>      vertices;
    vec2                grid;
    
    const GLuint        programID = glCreateProgram();
    
    GLuint              VAO;
    GLuint              buffer;
    
    GLuint              timeUniformLocation;
    GLuint              resolutionUniformLocation;
    GLuint              gridUniformLocation;
};
#endif /* __cplusplus */

// grid+.cpp
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    extern void setupGrid(char *basePath);
    extern void drawGrid(float deltaTime, int resolution[2]);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* grid_h */
