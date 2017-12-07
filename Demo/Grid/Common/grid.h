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
    Grid(std::string basePath, std::tuple<int, int> gridDimension);
    void            draw(time_t deltaTime);
private:
    std::vector<glm::vec2>  points;
    
    const GLuint            programID = glCreateProgram();
    
    GLuint                  vertexArrayObject;
    GLuint                  bufferObject;
    
    GLuint                  timeUniformLocation;
};
#endif /* __cplusplus */

// grid+.cpp
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    extern void setupGrid(char *basePath);
    extern void drawGrid();
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* grid_h */
