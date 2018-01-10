//
//  particle.hpp
//  OpenGL
//
//  Created by Hai Nguyen on 12/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef particles_hpp
#define particles_hpp

#include "utility.hpp"
#include "textures.hpp"

class Particles {
public:
    Particles(string basePath, vec2 size, vec2 resolution, Textures *textures);
    
    void            draw();
private:
    GLuint          program = glCreateProgram();
    
    Textures        *textures;
    vector<vec2>    vertices;
    
    vec2            resolution;

    GLuint          VBO;
    
    GLuint          resolutionUniformLocation;
    GLuint          positionsUniformLocation;
    GLuint          velocitiesUniformLocation;
    GLuint          texCoordAttributeLocation;
    
    void            _draw();
};
#endif /* particles_hpp */
