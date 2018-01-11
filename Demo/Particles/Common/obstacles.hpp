//
//  obstacles.hpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 1/8/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

#ifndef obstacles_hpp
#define obstacles_hpp

#include "utility.hpp"
#include "textures.hpp"

class Obstacles {
public:
    Obstacles(string basePath, vec2 resolution, Textures *textures);
    
    void            addObstacle(vec2 position);
    void            draw(GLint mode);
private:
    GLuint          program = glCreateProgram();
    
    Textures        *textures;
    vector<vec2>    vertices;
    vec2            resolution;
    
    GLuint          VBO;
    GLuint          FBO;
    
    GLuint          positionAttributeLocation;
    GLuint          modeUniformLocation;
};

#endif /* obstacles_hpp */
