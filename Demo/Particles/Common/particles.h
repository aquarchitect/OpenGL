//
//  particle.h
//  OpenGL
//
//  Created by Hai Nguyen on 12/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef particles_h
#define particles_h

// particles.cpp
#ifdef __cplusplus
#include "utility.hpp"

class Particles {
public:
    Particles(string basePath, vec2 grid, vec2 resolution);
    void    draw();
private:
    GLuint          program = glCreateProgram();
    
    vector<vec2>    vertices;
    vec2            grid;
    vec2            resolution;

    GLuint          VAO;
    GLuint          VBO;
    
    GLuint          resolutionUniformLocation;
    GLuint          gridUniformLocation;
};
#endif /* __cplusplus */

// particles+.cpp
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    extern void setupParticles(char *basePath, int resoltion[2]);
    extern void drawParticles(float deltaTime);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* particles_h */
