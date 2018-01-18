//
//  grid.hpp
//  Grid-iOS
//
//  Created by Hai Nguyen on 12/4/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef grid_hpp
#define grid_hpp

#ifdef __cplusplus
#include "utility.hpp"

class Grid {
public:
    Grid(string basePath, vec2 grid, vec2 resolution);
    void            draw(GLfloat deltaTime);
private:
    struct Vertex {
        GLfloat point[2];
        GLfloat index;
    };
    
    vector<Vertex>      vertices;
    vec2                grid;
    vec2                resolution;
    
    const GLuint        program = glCreateProgram();
    
    GLuint              VAO;
    GLuint              VBO;
    
    GLuint              timeUniformLocation;
    GLuint              resolutionUniformLocation;
    GLuint              gridUniformLocation;
};
#endif /* __cplusplus */
#endif /* grid_hpp */
