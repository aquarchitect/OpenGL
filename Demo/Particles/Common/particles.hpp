//
//  particle.hpp
//  OpenGL
//
//  Created by Hai Nguyen on 12/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef particles_hpp
#define particles_hpp

#ifdef __cplusplus
#include "utility.hpp"

class Particles {
public:
    Particles(string basePath, vec2 grid, vec2 resolution);
    void    draw();
private:
    struct RGBA { GLubyte r, g, b, a; };
    struct Textures { GLuint p0, p1, v0, v1; };
    
    GLuint          program = glCreateProgram();
    
    vector<vec2>    vertices;
    vec2            grid;
    vec2            resolution;

    GLuint          VAO;
    GLuint          VBO;
    
    Textures        textures;
    
    GLuint          positionUniformLocation;
    GLuint          resolutionUniformLocation;
    GLuint          gridUniformLocation;
    
    GLuint          createTexture(GLuint slot, GLvoid *pixels);
};
#endif /* __cplusplus */
#endif /* particles_hpp */
