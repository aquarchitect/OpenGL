//
//  update.hpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/18/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef update_hpp
#define update_hpp

#include "utility.hpp"
#include "textures.hpp"

class Update {
public:
    Update(string basePath, vec2 grid, vec2 resolution, Textures *textures);
    void draw();
private:    
    vector<vec2>    vertices = {
                        {-1.0, -1.0},
                        {-1.0, +1.0},
                        {+1.0, -1.0},
                        {+1.0, +1.0}
                    };
    
    GLuint          program = glCreateProgram();
    
    vec2            size;
    vec2            resolution;
    
    GLuint          count = 0;
    
    Textures        *textures;
    
    GLuint          VBO;
    GLuint          FBO;
    
    GLuint          resolutionUniformLocation;
    GLuint          positionsUniformLocation;
    GLuint          velocitiesUniformLocation;
    GLuint          modeUniformLocation;
    GLuint          positionAttributeLocation;
    GLuint          obstaclesUniformLocation;
    
    void            draw(GLint mode);
};

#endif /* update_hpp */
